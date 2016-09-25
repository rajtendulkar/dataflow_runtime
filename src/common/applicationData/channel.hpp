/*
 * channel.h
 *
 *  Created on: Dec 28, 2013
 *      Author: rajtendulkar
 */

#ifndef _CHANNEL_H
#define _CHANNEL_H
#include <fifo.hpp>
#include <fifoInfo.hpp>
#include <string>
class Actor;

class Channel
{
private:
public:
	string *name;
	Actor *srcActor;
	Actor *dstActor;
	unsigned int tokenSize;
	unsigned int channelSize;
	unsigned int initialTokens;
	unsigned int srcPortRate;
	unsigned int dstPortRate;
	unsigned int peekRate;
	unsigned int srcPort;
	unsigned int dstPort;
	FifoInfo *fifoInfo;
	Fifo *fifo;

	Channel()
	{
		tokenSize = 0;
		channelSize = 0;
		initialTokens = 0;
		srcPortRate = 0;
		dstPortRate = 0;
		peekRate = 0;
		srcPort = -1;
		dstPort = -1;
		fifo = NULL;
		fifoInfo = NULL;
		name = NULL;
		srcActor = NULL;
		dstActor = NULL;
	}

	~Channel()
	{
		if(fifo != NULL)
			delete fifo;
		if(fifoInfo != NULL)
			delete fifoInfo;
		delete name;
	}

	void print ()
	{
		cout << "Channel :" << *name << endl ;
		cout << "\tToken Size : " << tokenSize << endl;
		cout << "\tChannel Size : " << channelSize << endl;
		cout << "\tInitial Tokens : " << initialTokens << endl;
		cout << "\tSrc Rate : " << srcPortRate << endl;
		cout << "\tDst Rate : " << dstPortRate << endl;
		cout << "\tSrc Port : " << srcPort << endl;
		cout << "\tDst Port : " << dstPort << endl;
		cout << "\tPeek Rate : " << peekRate << endl;
		cout << "Fifo Info :: " << endl;
		if (fifo != NULL)
			fifo->print();
	}

	bool isInitialized ()
	{
		if((tokenSize == 0) && (channelSize == 0) && (initialTokens == 0) && (srcPortRate == 0) && (dstPortRate == 0))
			return false;
		else
			return true;
	}

	void initializeFifo ()
	{
		// Note : this is also done in the fifo.hpp
		if(peekRate < dstPortRate){
			peekRate = dstPortRate;
		}
		if(fifo == NULL)
			fifo = new Fifo(srcPortRate, dstPortRate, peekRate, initialTokens,
					tokenSize, fifoInfo->fifoSize, fifoInfo->sourceCluster, fifoInfo->destinationCluster);

	}

};

#endif /* _CHANNEL_H */
