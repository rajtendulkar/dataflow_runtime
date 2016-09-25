/*
 * averager.hpp
 *
 *  Created on: Jul 9, 2014
 *      Author: maselbas
 */

#ifndef AVERAGER_HPP_
#define AVERAGER_HPP_

#include <movingAverageParams.hpp>

#ifdef MOVINGAVERAGE_APP

#define N 10

class Averager : public ActorExecutor
{
private:

public:
	Averager (Actor *actor) : ActorExecutor(actor){}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		// pop 1 peek N
		int ** dataIn  = (int **)getFifoData(0);
		int ** dataOut = (int **)getFifoData(1);

		int sum = 0;
		for (int i=0; i < N; i++){
			sum += *(dataIn[i]);
		}
		*(dataOut[0]) = sum;
	}
};

#endif /* MOVINGAVERAGE_APP */

#endif /* AVERAGER_HPP_ */
