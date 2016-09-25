/*
 * dctJointer.hpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef DCTJOINER_HPP_
#define DCTJOINER_HPP_

#include <dctParams.hpp>

#ifdef DCT_APP
// Just re-arrange the outputs.
class DctJoiner : public ActorExecutor
{
private:
public:
	DctJoiner (Actor *actor) : ActorExecutor(actor) {}
	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **inputData = (int**)getFifoData(0);
		int **outputData = (int**)getFifoData(1);

		for(unsigned int i=0;i<SIZE;i++)
			for(unsigned int j=0;j<SIZE;j++)
				*(outputData[i*SIZE + j]) = *(inputData[j*SIZE + i]);

	}
};
#endif /* DCT_APP */
#endif /* DCTJOINER_HPP_ */
