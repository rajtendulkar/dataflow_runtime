/*
 * consumer.h
 *
 *  Created on: Dec 29, 2013
 *      Author: rajtendulkar
 */

#ifndef CONSUMEREMPTYAPP_H_
#define CONSUMEREMPTYAPP_H_

#include <emptyAppParams.hpp>

#ifdef EMPTY_APP

class Consumer : public ActorExecutor
{
private:

public:
	Consumer (Actor *actor) : ActorExecutor(actor)
	{
	}

	~Consumer()
	{
	}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
	}
};

#endif /* EMPTY_APP */
#endif /* CONSUMEREMPTYAPP_H_ */
