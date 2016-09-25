/*
 * Delay.hpp
 *
 *  Created on: Jun 30, 2014
 *      Author: maselbas
 */

#ifndef DELAY_HPP_
#define DELAY_HPP_
/*
class Delay : public ActorExecutor
{
private:
	int n_delay;
public:
	Delay (Actor *actor, int N) : ActorExecutor(actor), n_delay(N) {}

	void init (unsigned int instanceId) {
		Fifo *fifo = getFifo(1);
		fifo->initialTokens = n_delay;
	}

	void execute (unsigned int instanceId, unsigned int iterationId){
		float ** dataIn  = (float**)getFifoData(0);
		float ** dataOut = (float**)getFifoData(1);

		*(dataOut[0]) = *(dataIn[0]);

	}
};

*/

#endif /* DELAY_HPP_ */
