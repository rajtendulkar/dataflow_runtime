/*
 * contract.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef CONTRACT_HPP_
#define CONTRACT_HPP_

#include <tdeParams.hpp>

#ifdef TDE_APP
class Contract : public ActorExecutor
{
private:
public:
	Contract (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **inputData = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);

		for (int i=0; i<2*N; i++)
			*(outputData[i]) = *(inputData[i]);
	}
};

#endif /* TDE_APP */
#endif /* CONTRACT_HPP_ */
