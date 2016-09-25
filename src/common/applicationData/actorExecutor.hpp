/*
 * actorExecutor.h
 *
 *  Created on: Dec 30, 2013
 *      Author: rajtendulkar
 */

#ifndef ACTOREXECUTOR_HPP_
#define ACTOREXECUTOR_HPP_

#include <actor.hpp>
#include <parameters.hpp>
#include <stdint.h>
#include <unistd.h>


typedef enum
{
	INPUT_FIFO,
	OUTPUT_FIFO
}FifoType;

class ActorExecutor
{
private:
	void ***fifoData;
protected:
	Actor *actor;
	FifoType *fifoType;

	//protected method
	inline void** getFifoData(unsigned int index) const { return fifoData[index]; }

public:
	ActorExecutor(Actor *actor)
	{
		this->actor = actor;

		int numFifo = actor->getNumPorts();
		fifoType = new FifoType[numFifo];
		fifoData = (void***) new void** [numFifo];
		for(int i=0;i<numFifo;i++)
		{
			Channel *chnnl = actor->getPort(i);
			if ((chnnl->srcActor != NULL) && (chnnl->srcActor == actor))
			{
				fifoData[i] = new void* [chnnl->fifo->srcPortRate];
				fifoType[i] = OUTPUT_FIFO;
			}
			else if ((chnnl->dstActor != NULL) && (chnnl->dstActor == actor))
			{
				fifoData[i] = new void* [chnnl->fifo->peekRate];
				fifoType[i] = INPUT_FIFO;
			}
			else
			{
				cout << "Channels source and destination actor don't match." << endl;
				assert(0);
			}
		}
	}

	virtual ~ActorExecutor()
	{
		for(unsigned int i=0;i<actor->getNumPorts();i++)
			delete [] fifoData[i];
		delete [] fifoData;
		delete [] fifoType;
	}

	void startFifo (int instanceId, int iterationId)
	{
		unsigned int instances = actor->instances;
		for(unsigned int i=0;i<actor->getNumPorts();i++)
		{
			Fifo *fifo = actor->getPort(i)->fifo;

#ifdef INTER_ITERATION_FIFO_FLUSH
			if (fifoType[i] == INPUT_FIFO)
				fifo->startFifoReader(((instances * 0) + instanceId), fifoData[i]);
			else if (fifoType[i] == OUTPUT_FIFO)
				fifo->startFifoWriter(((instances * 0) + instanceId), fifoData[i]);
#else
			if (fifoType[i] == INPUT_FIFO)
				fifo->startFifoReader(((instances * iterationId) + instanceId), fifoData[i]);
			else if (fifoType[i] == OUTPUT_FIFO)
				fifo->startFifoWriter(((instances * iterationId) + instanceId), fifoData[i]);

#endif
		}
	}

	void endFifo (int instanceId, int iterationId)
	{
		unsigned int instances = actor->instances;

		// We give the priority to the intra-cluster FIFO.
		for(unsigned int i=0;i<actor->getNumPorts();i++)
		{
			Fifo *fifo = actor->getPort(i)->fifo;
			if(fifo->sourceCluster == fifo->destinationCluster)
			{
#ifdef INTER_ITERATION_FIFO_FLUSH
				if (fifoType[i] == INPUT_FIFO)
					fifo->endFifoReader(((instances * 0) + instanceId), instanceId);
				else if (fifoType[i] == OUTPUT_FIFO)
					fifo->endFifoWriter(((instances * 0) + instanceId), instanceId);

#else
				if (fifoType[i] == INPUT_FIFO)
					fifo->endFifoReader(((instances * iterationId) + instanceId), instanceId);
				else if (fifoType[i] == OUTPUT_FIFO)
					fifo->endFifoWriter(((instances * iterationId) + instanceId), instanceId);
#endif
			}
		}

		// Now we perform the inter-cluster FIFO.
		for(unsigned int i=0;i<actor->getNumPorts();i++)
		{
			Fifo *fifo = actor->getPort(i)->fifo;
			if(fifo->sourceCluster != fifo->destinationCluster)
			{
#ifdef INTER_ITERATION_FIFO_FLUSH
				if (fifoType[i] == INPUT_FIFO)
					fifo->endFifoReader(((instances * 0) + instanceId), instanceId);
				else if (fifoType[i] == OUTPUT_FIFO)
					fifo->endFifoWriter(((instances * 0) + instanceId), instanceId);
#else
				if (fifoType[i] == INPUT_FIFO)
					fifo->endFifoReader(((instances * iterationId) + instanceId), instanceId);
				else if (fifoType[i] == OUTPUT_FIFO)
					fifo->endFifoWriter(((instances * iterationId) + instanceId), instanceId);
#endif
			}
		}
	}

	Fifo *getFifo(unsigned int index) { return actor->getFifo(index); }
	virtual void init (unsigned int instanceId) = 0;
	virtual void execute (unsigned int instanceId, unsigned int iterationId) = 0;
};

#endif /* ACTOREXECUTOR_HPP_ */
