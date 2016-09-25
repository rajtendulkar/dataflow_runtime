/*
 * rearrangeIndices.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef REARRANGEINDICES_HPP_
#define REARRANGEINDICES_HPP_

#include <ccParams.hpp>

#ifdef COMPARISON_COUNTING
class RearrangeIndices : public ActorExecutor
{
private:
public:
	RearrangeIndices (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **inputData1 = (int**)getFifoData(0);
		int **inputData2 = (int**)getFifoData(1);
		int **outputData = (int**)getFifoData(2);

	    for (int i = 0; i < SIZE; i++)
            *(outputData[*(inputData1[i])]) = *(inputData2[i]);
	}
};

#endif /* COMPARISON_COUNTING */



#endif /* REARRANGEINDICES_HPP_ */
