/*
 * consumer.h
 *
 *  Created on: Dec 29, 2013
 *      Author: rajtendulkar
 */

#ifndef CONSUMER_HPP_
#define CONSUMER_HPP_

#include <fifoAppParams.hpp>
#include <cluster_defs.hpp>

#ifdef FIFO_TEST_APP

class Consumer : public ActorExecutor
{
private:
	unsigned int dstRate;
	unsigned int numDstInstances;
	unsigned int tokenSize;

public:
	Consumer (Actor *actor) : ActorExecutor(actor)
	{
		Fifo *fifo = getFifo(0);
		dstRate = fifo->dstPortRate;
		numDstInstances = actor->instances;
		tokenSize = fifo->tokenSize;
	}

	~Consumer() {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		unsigned char **data = (unsigned char**)getFifoData(0);
		cout << *(actor->name) << instanceId << " on -- " << getClusterId() << " :: " << getProcId() << endl;

		for(unsigned int i=0;i<dstRate;i++)
			for(unsigned int j=0;j<tokenSize;j++)
			{
				unsigned char expectedData = (iterationId * numDstInstances * dstRate * tokenSize)
											+ (instanceId * dstRate * tokenSize)
											+ (i*tokenSize)
											+ j;

				if(data[i][j] != expectedData)
					cout << "Iteration :" << iterationId << " Consumer :" <<
						instanceId << " Expected :" << expectedData << " Found : " << data[i][j] << endl;
			}

		cout << *(actor->name) << instanceId << "Finished" << endl;
	}
};

#endif /* FIFO_TEST_APP */
#endif /* CONSUMER_HPP_ */
