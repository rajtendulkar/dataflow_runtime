/*
 * producer.h
 *
 *  Created on: Dec 29, 2013
 *      Author: rajtendulkar
 */

#ifndef PRODUCER_HPP_
#define PRODUCER_HPP_

#include <fifoAppParams.hpp>
#include <cluster_defs.hpp>
#include <actorExecutor.hpp>

#ifdef FIFO_TEST_APP

class Producer : public ActorExecutor
{
private:
	unsigned int srcRate;
	unsigned int numSrcInstances;
	unsigned int tokenSize;

public:
	Producer(Actor *actor) : ActorExecutor(actor)
	{
		Fifo *fifo = getFifo(0);
		srcRate = fifo->srcPortRate;
		numSrcInstances = actor->instances;
		tokenSize = fifo->tokenSize;
	}

	~Producer() { }

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		unsigned char **data = (unsigned char**)getFifoData(0);
		cout << *(actor->name) << instanceId << " on -- " << getClusterId() << " :: " << getProcId() << endl;


		for(unsigned int i=0;i<srcRate;i++)
			for(unsigned int j=0;j<tokenSize;j++)
				data[i][j] = (iterationId * numSrcInstances * srcRate * tokenSize)
				+ (instanceId * srcRate * tokenSize)
				+ (i*tokenSize)
				+ j;

		cout << *(actor->name) << instanceId << " Finished" << endl;
	}
};
#endif /* FIFO_TEST_APP */
#endif /* PRODUCER_HPP_ */
