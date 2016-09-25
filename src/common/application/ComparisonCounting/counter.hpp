/*
 * counter.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef COUNTER_HPP_
#define COUNTER_HPP_

#include <ccParams.hpp>

#ifdef COMPARISON_COUNTING
class Counter : public ActorExecutor
{
private:
public:
	Counter (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **inputData = (int**)getFifoData(0);
		int **outputData = (int**)getFifoData(1);

        int mine = *(inputData[instanceId]);
        int count = 0;

        for (int i = 0; i < SIZE; i++)
        {
            if (*(inputData[i]) < mine)
                count = count + 1;
        }

        *(outputData[0]) = count;
	}
};

#endif /* COMPARISON_COUNTING */
#endif /* COUNTER_HPP_ */
