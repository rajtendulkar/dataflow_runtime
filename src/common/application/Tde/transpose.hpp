/*
 * transpose.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef TRANSPOSE_HPP_
#define TRANSPOSE_HPP_

#include <tdeParams.hpp>

#ifdef TDE_APP
class Transpose : public ActorExecutor
{
private:
public:
	Transpose (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **inputData = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);
		int outputCount = 0;

		for(int i=0; i<M; i++)
		{
			for(int j=0; j<N; j++)
			{
				*(outputData[outputCount++]) = *(inputData[i*N*2+j*2]);
				*(outputData[outputCount++]) = *(inputData[i*N*2+j*2+1]);
			}
		}
	}
};
#endif /* TDE_APP */
#endif /* TRANSPOSE_HPP_ */
