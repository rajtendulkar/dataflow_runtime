/*
 * multiplyByFloat.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef MULTIPLYBYFLOAT_HPP_
#define MULTIPLYBYFLOAT_HPP_

#include <tdeParams.hpp>

#ifdef TDE_APP
class MultiplyByFloat : public ActorExecutor
{
private:

public:
	MultiplyByFloat (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **inputData = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);

		for (int i=0; i<2*B; i++)
			*(outputData[i]) = *(inputData[i]) * mult;
	}
};
#endif /* TDE_APP */


#endif /* MULTIPLYBYFLOAT_HPP_ */
