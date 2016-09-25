/*
 * countSplit.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef COUNTSPLIT_HPP_
#define COUNTSPLIT_HPP_

#include <ccParams.hpp>

#ifdef COMPARISON_COUNTING
class CountSplit : public ActorExecutor
{
private:
public:
	CountSplit (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **inputData = (int**)getFifoData(0);
		int **outputData = (int**)getFifoData(1);

		for(int i=0;i<SIZE;i++)
			for(int j=0;j<SIZE;j++)
				*(outputData[i*SIZE+j]) = *(inputData[j]);
	}
};

#endif /* COMPARISON_COUNTING */


#endif /* COUNTSPLIT_HPP_ */
