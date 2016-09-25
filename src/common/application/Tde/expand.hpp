/*
 * expand.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef EXPAND_HPP_
#define EXPAND_HPP_

#include <tdeParams.hpp>

#ifdef TDE_APP
class Expand : public ActorExecutor
{
private:

public:
	Expand (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **inputData = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);

		for (int i=0; i<2*N; i++)
			*(outputData[i]) = *(inputData[i]);

		for (int i=2*N; i<2*B; i++)
			*(outputData[i]) = 0.0;
	}
};
#endif /* TDE_APP */
#endif /* EXPAND_HPP_ */
