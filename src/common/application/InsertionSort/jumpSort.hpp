/*
 * jumpSort.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef JUMPSORT_HPP_
#define JUMPSORT_HPP_

#include <insertionSortParams.hpp>

#ifdef INSERTION_SORT
class JumpSort : public ActorExecutor
{
private:
	int start;
public:
	JumpSort (Actor *actor) : ActorExecutor(actor)
	{
		start = -1;
	}

	void init (unsigned int instanceId)
	{
		string actorNamePrefix = "JumpSort";
		string *name = actor->name;
		string index = name->substr(actorNamePrefix.length());
		int indexNum = atoi(index.c_str());

		start = indexNum;
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **inputData = (int**)getFifoData(0);
		int **outputData = (int**)getFifoData(1);
        int keep = 1;


        for (int j = start; j < SIZE; j++)
        {
            int current = *(inputData[j]);
            int i;
            keep = 1;
            for (i = j - start; i >= 0 && (keep == 1); i = i - start)
            {
                if (*(inputData[i]) <= current)
                {
                    keep = 0;
                    i = i + start;
                }
                else
                {
                    *(inputData[i + start]) = *(inputData[i]);
                }
            }
            *(inputData[i + start]) = current;
        }

        for (int i = 0; i < SIZE; i++)
            *(outputData[i]) = *(inputData[i]);
	}
};

#endif /* INSERTION_SORT */
#endif /* JUMPSORT_HPP_ */
