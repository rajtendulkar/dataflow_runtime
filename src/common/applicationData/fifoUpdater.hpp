/*
 * fifoUpdater.hpp
 *
 *  Created on: Feb 4, 2014
 *      Author: rajtendulkar
 */

#ifndef FIFOUPDATER_HPP_
#define FIFOUPDATER_HPP_

#include <shared_defs.hpp>
#include <fifo.hpp>
#include <applicationData.hpp>

class FifoTxStatusUpdater : public ActorExecutor
{
private:

public:
	FifoTxStatusUpdater (Actor *actor) : ActorExecutor(actor)
	{
	}

	void init(unsigned int instanceId)
	{
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
	}
};

#endif /* FIFOUPDATER_HPP_ */
