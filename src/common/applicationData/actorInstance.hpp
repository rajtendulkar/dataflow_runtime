/*
 * ActorInstance.h
 *
 *  Created on: Dec 28, 2013
 *      Author: rajtendulkar
 */

#ifndef ACTORINSTANCE_H_
#define ACTORINSTANCE_H_

#include <actorExecutor.hpp>
#include <cluster_defs.hpp>

class ActorInstance
{
private:
public:
	int exeIter;
	unsigned int instanceId;
	Actor *actor;
	ActorExecutor *executor;

	~ActorInstance()
	{
		if(executor != NULL)
			delete executor;
	}

	ActorInstance()
	{
		instanceId = 0;
		actor = NULL;
		executor = NULL;
		this->exeIter = 0;

	}

	ActorInstance(int instanceId, Actor *actor)
	{
		this->actor = actor;
		this->instanceId = instanceId;
		this->executor = NULL;
		this->exeIter = 0;
	}

	ActorInstance(int instanceId, Actor *actor, ActorExecutor *executor)
	{
		this->actor = actor;
		this->instanceId = instanceId;
		this->executor = executor;
		this->exeIter = 0;
	}

	void print()
	{
		cout << "\tActor : " << *(actor->name) << " Instance : " << instanceId
				<< "  Exe Iteration : "<< exeIter <<endl;
	}

	void execute(){
		// Start all the FIFO Readers and Writers.
		executor->startFifo(instanceId, exeIter);

		// Execute the Actor Instance.
		executor->execute  (instanceId, exeIter);

		// End all the FIFO Readers and Writers.
		executor->endFifo  (instanceId, exeIter);

		this->exeIter++;
	}
};

#endif /* ACTORINSTANCE_H_ */
