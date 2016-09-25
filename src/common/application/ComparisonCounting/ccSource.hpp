/*
 * insertionSource.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef CCSOURCE_HPP_
#define CCSOURCE_HPP_

#include <ccParams.hpp>

#ifdef COMPARISON_COUNTING
class IntSource : public ActorExecutor
{
private:
	int intData[SIZE];
public:
	IntSource (Actor *actor) : ActorExecutor(actor)
	{
		intData[0] = 503;
        intData[1] = 87;
        intData[2] = 512;
        intData[3] = 61;
        intData[4] = 908;
        intData[5] = 170;
        intData[6] = 897;
        intData[7] = 275;
        intData[8] = 653;
        intData[9] = 426;
        intData[10] = 154;
        intData[11] = 509;
        intData[12] = 612;
        intData[13] = 677;
        intData[14] = 765;
        intData[15] = 703;
	}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **data1 = (int**)getFifoData(0);
		int **data2 = (int**)getFifoData(1);

		// Write to FIFO
		for(int i=0;i<SIZE;i++)
		{
			*(data1[i]) = intData[i];
			*(data2[i]) = intData[i];
		}
	}
};

#endif /* COMPARISON_COUNTING */
#endif /* CCSOURCE_HPP_ */
