/*
 * dctInputGenerate.cpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef DCTINPUTGENERATE_HPP_
#define DCTINPUTGENERATE_HPP_

#include <dctParams.hpp>

#ifdef DCT_APP
// Just re-arrange the outputs.
class DctInputGenerate : public ActorExecutor
{
private:
public:
	DctInputGenerate (Actor *actor) : ActorExecutor(actor) {}
	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **outputData = (int**)getFifoData(0);

		for(unsigned int i=0;i<SIZE*SIZE;i++)
			*(outputData[i]) = i;
	}
};
#endif /* DCT_APP */
#endif /* DCTINPUTGENERATE_HPP_ */
