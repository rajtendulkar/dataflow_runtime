/*
 * fifo.c
 *
 *  Created on: Dec 29, 2013
 *      Author: rajtendulkar
 */


#include <fifo.hpp>
#include <shared_defs.hpp>
#include <applicationData.hpp>
#include <errno.h>

#include <cmath>

static string tokenStatusString (TokenStatus status)
{
	switch(status)
	{
		case TOKEN_IS_EMPTY:
			return "TOKEN_IS_EMPTY";
			break;

		case TOKEN_IS_BEING_READ:
			return "TOKEN_IS_BEING_READ";
			break;

		case TOKEN_IS_BEING_WRITTEN:
			return "TOKEN_IS_BEING_WRITTEN";
			break;

		case TOKEN_CONTAINS_DATA:
			return "TOKEN_CONTAINS_DATA";
			break;

		default:
			return "INVALID TOKEN STATUS";
			break;
	}
	return "INVALID TOKEN STATUS";
}

void Fifo::print (bool printTokenData)
{
	cout << "Fifo Info :: " << this  << endl;
	cout << "SrcRate : " << srcPortRate << " DstRate : " << dstPortRate
			<< " fifo size :" << fifoSize << " token size :" << tokenSize
			<< " src cluster : " << sourceCluster << " dst cluster : " << destinationCluster
			<< endl;

	cout << "Token Access" << endl;

	for(unsigned int i=0;i<fifoSize;i++)
	{
		// Remember that each token status is after the token data.
		TokenAccess *accessPtr = getTokenStatusOffset(i);
		cout << "Token " << i
			<< " index : " << accessPtr->tokenIndex
			<< " Status : " << accessPtr->tokenStatus << " " << tokenStatusString(accessPtr->tokenStatus)
			<< endl;
	}

	if(printTokenData == 1)
	{
		cout << "Fifo Data" << endl;
		for(unsigned int i=0;i<fifoSize;i++)
		{
			unsigned char *dataPtr = getTokenDataOffset(i);
			cout << endl << "Token "<< i << endl;
			for(unsigned j=0;j<tokenSize;j++)
				cout << hex << (int)dataPtr[i*tokenSize + j] << " ";
			cout << endl;
		}
		cout << endl;
	}
}

static int tokenAccessEquals (TokenAccess *x, TokenAccess *y, mutex_t *lock)
{
	int result = 0;
	mutex_lock(lock);
	result =  ((x->tokenIndex == y->tokenIndex) && (x->tokenStatus == y->tokenStatus));
	mutex_unlock(lock);
	return result;
}

// Warning : This function can be implemented without lock since SDU works in atomic fashion
// and TokenAccess field is of 8 bytes.
static void updateTokenAccess (TokenAccess* updated_access, TokenAccess *new_access, mutex_t *lock)
{
	mutex_lock(lock);
	*updated_access = *new_access;
	mutex_unlock(lock);
}

static inline void waitUntilAccess(TokenAccess* tested_access, TokenAccess *required_access, mutex_t *lock)
{
	// Busy wait till the requested token access is available.
	while (!tokenAccessEquals(tested_access, required_access, lock));
}

/*
 * decrement the value of count,
 * return the old value of count
 */
static unsigned int decrementTokenCount(unsigned int *count, mutex_t *lock){
	unsigned int old_count;
	mutex_lock(lock);
	old_count = *count;
	*count= old_count -1;
	mutex_unlock(lock);
	return old_count;
}
/*
 * decrement the value of count,
 * test if the count value is < 0 set it with val
 * return the old value of count
 */
/*static unsigned int testSetTokenCount(unsigned int *count, int val, mutex_t *lock){
	unsigned int old_count;
	mutex_lock(lock);
	old_count = *count;
	*count= old_count -1;
	if(*count == 0){
		*count = val;
	}
	mutex_unlock(lock);
	return old_count;
}
*/

void Fifo::resetFifo()
{
	memset(dataAndTokenPtr, 0, (((sizeof(unsigned char) * alignedTokenSize) + sizeof(TokenAccess)) * fifoSize) );

	int m = ceil((float)peekRate/(float)dstPortRate);

	for (unsigned int i=0;i<fifoSize;i++)
	{
		TokenAccess *accessPtr = getTokenStatusOffset(i);
		accessPtr->tokenIndex = i;
		accessPtr->tokenStatus = TOKEN_IS_EMPTY;

		//initialize token's peekcount
		peekCount[i] = ( i < (m-1)*dstPortRate)? ceil(i/dstPortRate)+1 : m;

	}

	//initials Tokens
	for(unsigned int i = 0; i < initialTokens && i < fifoSize; i++){
		TokenAccess *accessPtr = getTokenStatusOffset(i);
		accessPtr->tokenStatus = TOKEN_CONTAINS_DATA;
	}

}

void Fifo::startFifoWriter (int iterationId, void **requestedDataPointer)
{
	int index = (iterationId * srcPortRate) + initialTokens;
	int positionInFifo = index % fifoSize;

	TokenAccess requiredAccess;
	requiredAccess.tokenStatus = TOKEN_IS_EMPTY;

	TokenAccess newTokenAccess;
	newTokenAccess.tokenStatus = TOKEN_IS_BEING_WRITTEN;


	for(unsigned int i=0 ; i<srcPortRate; i++, index++, positionInFifo=(positionInFifo+1)%fifoSize)
	{
		TokenAccess *accessPtr = getTokenStatusOffset(positionInFifo);
		requiredAccess.tokenIndex = index;
		newTokenAccess.tokenIndex = index;

		WAIT_UNTIL_ACCESS (accessPtr, &requiredAccess);
		UPDATE_TOKEN_ACCESS (accessPtr, &newTokenAccess);

		requestedDataPointer[i] = getTokenDataOffset(positionInFifo);
	}

}

void Fifo::endFifoWriter (int iterationId, int instanceId)
{
	int index = (iterationId * srcPortRate) + initialTokens;
	int positionInFifo = index % fifoSize;
	TokenAccess newTokenAccess;
	newTokenAccess.tokenStatus = TOKEN_CONTAINS_DATA;

	for(unsigned int i=0 ; i<srcPortRate; i++, index++, positionInFifo=(positionInFifo+1)%fifoSize)
	{
		TokenAccess *accessPtr = getTokenStatusOffset(positionInFifo);
		newTokenAccess.tokenIndex = index;

		UPDATE_TOKEN_ACCESS (accessPtr, &newTokenAccess);
	}

}

void Fifo::startFifoReader (int iterationId, void **requestedDataPointer)
{
	int index = (iterationId * dstPortRate);
	int positionInFifo = index % fifoSize;
	TokenAccess requiredAccess;
	requiredAccess.tokenStatus = TOKEN_CONTAINS_DATA;

	//Note: only need token containing data, to be able to have more than 1 reader at the same time
	//      use peekRate instead of dstRate for more info see fifo.hpp
	for(unsigned int i=0; i<peekRate; i++, index++,positionInFifo=(positionInFifo+1)%fifoSize){
		TokenAccess *accessPtr = getTokenStatusOffset(positionInFifo);
		requiredAccess.tokenIndex = index;

		WAIT_UNTIL_ACCESS (accessPtr, &requiredAccess);

		requestedDataPointer[i] = getTokenDataOffset(positionInFifo);
	}

}

void Fifo::endFifoReader (int iterationId, int instanceId)
{
	int index = (iterationId * dstPortRate);
	int positionInFifo = index % fifoSize;
	int m = ceil((float)peekRate/(float)dstPortRate);


	TokenAccess newTokenAccess;
	newTokenAccess.tokenStatus = TOKEN_IS_EMPTY;

	//Note: only release token if this is the last reader, the peek count is used for that
	//      use peekRate instead of dstRate for more info see fifo.hpp
	for(unsigned int i=0 ; i<peekRate; i++, index++, positionInFifo=(positionInFifo+1)%fifoSize)
	{
		unsigned int old_count = DECREMENT_TOKEN_COUNT(peekCount+positionInFifo);
		if( old_count == 1){ // this mean we are the last reader
		// if(--peekCount[positionInFifo] == 0){// atomic fashion not so good
			peekCount[positionInFifo] = m;		// no more reader, dont need mutex
			TokenAccess *accessPtr = getTokenStatusOffset(positionInFifo);
			newTokenAccess.tokenIndex = (index + fifoSize);
			UPDATE_TOKEN_ACCESS (accessPtr, &newTokenAccess);

		}

	}
}

