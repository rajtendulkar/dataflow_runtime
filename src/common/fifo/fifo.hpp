/*
 * fifo.h
 *
 *  Created on: Dec 29, 2013
 *      Author: rajtendulkar
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <lock.h>
#include <assert.h>
#include <parameters.hpp>

using namespace std;

#define WAIT_UNTIL_ACCESS(A,B) waitUntilAccess(A,B,&(dataTxLock))
#define UPDATE_TOKEN_ACCESS(A,B) updateTokenAccess(A, B, &(dataTxLock))

//#define TEST_SET_TOKEN_COUNT(A,B) testSetTokenCount(A, B, &(countRxLock))
#define DECREMENT_TOKEN_COUNT(A) decrementTokenCount(A, &(countRxLock))



#define getTokenDataOffset(index) (unsigned char*)(dataAndTokenPtr													\
								+ (index*(sizeof(unsigned char)*alignedTokenSize + sizeof(TokenAccess))));


#define getTokenStatusOffset(index) (TokenAccess *)(dataAndTokenPtr													\
									+ (index*(sizeof(unsigned char)*alignedTokenSize + sizeof(TokenAccess)))		\
									+ (sizeof(unsigned char)*alignedTokenSize));

typedef enum
{
	TOKEN_IS_EMPTY,
	TOKEN_IS_BEING_READ,
	TOKEN_IS_BEING_WRITTEN,
	TOKEN_CONTAINS_DATA
}TokenStatus;

// Declare the class Fifo so that we can have a pointer to it in token access.
class Fifo;

typedef union
{
	// I will store the token status.
	// Remember that this will be atomic write by the portal since it is aligned to the 8-byte boundary.
	// But just to be sure, let the tokenStatus be the last element
	struct
	{
		volatile unsigned int tokenIndex;
		volatile TokenStatus tokenStatus;
	};
	// It should always be 8-bytes so that we can safely use LDU/SDU instructions without lock.
	// Requirement for this is alignment on 8-byte boundary.
	unsigned long long longVar;
}__attribute__((packed, aligned(8))) TokenAccess;

class Fifo
{
private :
	unsigned int *peekCount;
	unsigned char *dataAndTokenPtr;
	mutex_t	dataTxLock;
	mutex_t countRxLock;

public:
	unsigned int fifoSize;
	unsigned int tokenSize;
	unsigned int alignedTokenSize;
	unsigned int srcPortRate;
	unsigned int dstPortRate;
	unsigned int sourceCluster;
	unsigned int destinationCluster;
	unsigned int initialTokens;
	unsigned int peekRate;

	Fifo (unsigned int srcPortRate, unsigned int dstPortRate,
			unsigned int peekRate,  unsigned int initialTokens,
			unsigned int tokenSize, unsigned int fifoSize,
			unsigned int sourceCluster, unsigned int destinationCluster )
	{

	     //cout << "Create Fifo " << " Src rate " << srcPortRate << " Dst Rate " << dstPortRate
	     //      << " token Size " << tokenSize << " fifosize " << fifoSize
	     //       << " src clus " << sourceCluster << " dst clus " << destinationCluster << endl;

		this->srcPortRate = srcPortRate;
		this->dstPortRate = dstPortRate;

		//Note that the dstPortRate is needed only if the peekRate is greater than the dstPortRate
		//		because a peek rate lesser than a pop rate (dstPortRate) mean nothing
		if(peekRate > this->dstPortRate){
			this->peekRate = peekRate;
		}else{
			this->peekRate = this->dstPortRate;
		}

		this->initialTokens = initialTokens;

		this->tokenSize = tokenSize;
		this->fifoSize = fifoSize;
		this->sourceCluster = sourceCluster;
		this->destinationCluster = destinationCluster;

		mutex_init(&(dataTxLock), NULL);
		mutex_init(&(countRxLock), NULL);


		// we create an alignment of 8-byte boundary for each token.
		// its easy to maintain a few things like sending data and token status together over portal.
		// without this we would have alignment issues for token status.
		alignedTokenSize = tokenSize;
		if(tokenSize % sizeof(unsigned long long) != 0)
			alignedTokenSize += (sizeof(unsigned long long) - (tokenSize % sizeof(unsigned long long)));

		// cout << "Aligned size : " << alignedTokenSize << " actual size : " << tokenSize << endl;
		try{
			peekCount = new unsigned int [fifoSize];
			dataAndTokenPtr = new unsigned char [(alignedTokenSize * fifoSize) + (sizeof(TokenAccess) * fifoSize)];
		}
		catch (exception & e) {
			cout << "== Unable to create fifo : " << e.what() << " == size : "<< ((alignedTokenSize * fifoSize) + (sizeof(TokenAccess) * fifoSize)) << " == " <<  endl
					<< " Src rate " << srcPortRate << " Dst Rate " << dstPortRate
					<< " token Size " << tokenSize << " fifosize " << fifoSize
					<< " src clus " << sourceCluster << " dst clus " << destinationCluster << endl;
			throw e;
		}
		resetFifo();
	}

	~Fifo()
	{
		delete [] dataAndTokenPtr;
		mutex_destroy(&(dataTxLock));
		mutex_destroy(&(countRxLock));

	}

	void print (bool printTokenData=0);
	void resetFifo();
	void startFifoWriter (int iterationId, void **requestedDataPointer);
	void endFifoWriter (int iterationId, int instanceId);
	void startFifoReader (int iterationId, void **requestedDataPointer);
	void endFifoReader (int iterationId, int instanceId);
};
#endif /* FIFO_H_ */
