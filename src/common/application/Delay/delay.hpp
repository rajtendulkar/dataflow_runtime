/*
 * delay.hpp
 *
 * 	Created on: Jun 16, 2014
 * 		Author: maselbas
 */

#ifndef DELAY_HPP_
#define DELAY_HPP_

#include <delayParams.hpp>
#include <cluster_defs.hpp>


#ifdef DELAY_APP


class Delay : public ActorExecutor {
private:
public:
	Delay(Actor *actor) : ActorExecutor(actor) {}

	void init(unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){
		//instanceId % fifo->fifoSize

		int **dataSrc = (int**)getFifoData(0);
		int **dataDst = (int**)getFifoData(1);

		*(dataDst[0] ) = *(dataSrc[0]);



	}

};


#endif /* DELAY_APP */

#endif /* DELAY_HPP_ */
