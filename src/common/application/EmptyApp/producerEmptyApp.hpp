/*
 * producer.h
 *
 *  Created on: Dec 29, 2013
 *      Author: rajtendulkar
 */

#ifndef PRODUCEREMPTYAPP_H_
#define PRODUCEREMPTYAPP_H_

#include <emptyAppParams.hpp>

#ifdef EMPTY_APP

class Producer : public ActorExecutor
{
private:

public:
	Producer(Actor *actor) : ActorExecutor(actor)
	{
	}

	~Producer()
	{
	}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
	}
};
#endif /* EMPTY_APP */
#endif /* PRODUCEREMPTYAPP_H_ */
