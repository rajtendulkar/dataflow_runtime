/*
 * fifo.h
 *
 *  Created on: Dec 28, 2013
 *      Author: rajtendulkar
 */

#ifndef FIFOINFO_H_
#define FIFOINFO_H_

#include <shared_defs.hpp>

class FifoInfo
{
private:
public:
	string *name;
	unsigned int sourceCluster;
	unsigned int destinationCluster;
	unsigned int fifoSize;
	unsigned int dstTokenPortalTag;
	unsigned int srcStatusPortalTag;
	unsigned int srcMaxWriters;
	unsigned int dstMaxWriters;

	FifoInfo()
	{
		sourceCluster = 0;
		destinationCluster = 0;
		fifoSize = 0;
		dstTokenPortalTag = 0;
		srcStatusPortalTag = 0;
		name = NULL;
		srcMaxWriters = 0;
		dstMaxWriters = 0;
	}

	~FifoInfo ()
	{
		delete name;
	}

	void print()
	{
		cout << "Fifo : " << name << endl;
		cout << "\tSource Cluster : " << sourceCluster << endl;
		cout << "\tDestination Cluster : " << destinationCluster << endl;
		cout << "\tFifo Size : " << fifoSize << endl;
		cout << "\tDestination Token Portal Tag : " << dstTokenPortalTag << endl;
		cout << "\tSource Status Portal Tag : " << srcStatusPortalTag << endl;
	}

	bool isInitialized()
	{
		if(sourceCluster == 0 && destinationCluster == 0 && fifoSize == 0
			&& dstTokenPortalTag == 0  && srcStatusPortalTag == 0)
			return false;
		else
			return true;
	}

};

#endif /* FIFOINFO_H_ */
