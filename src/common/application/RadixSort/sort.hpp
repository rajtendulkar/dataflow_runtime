/*
 * sort.hpp
 *
 *  Created on: Jan 9, 2014
 *      Author: rajtendulkar
 */

#ifndef SORT_HPP_
#define SORT_HPP_

#include <radixSortParams.hpp>

#ifdef RADIX_SORT
class Sort : public ActorExecutor
{
private:
	int radix;
	int ordering[SIZE];
public:
	Sort (Actor *actor) : ActorExecutor(actor)
	{
		radix = -1;
	}

	void init (unsigned int instanceId)
	{
		string actorNamePrefix = "Radix";
		string *name = actor->name;
		string index = name->substr(actorNamePrefix.length());
		int indexNum = atoi(index.c_str());

		radix = (int)pow(2, indexNum);
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **inputData = (int**)getFifoData(0);
		int **outputData = (int**)getFifoData(1);

		int j = 0, outputCount = 0;
        for (int i = 0; i < SIZE; i++)
        {
            int current = *(inputData[i]);
            if ((current & radix) == 0)
            {
                *(outputData[outputCount++]) = current;
            }
            else
            {
                ordering[j] = current;
                j = j + 1;
            }
        }
        for (int i = 0; i < j; i++)
        	*(outputData[outputCount++]) = ordering[i];
	}
};

#endif /* RADIX_SORT */


#endif /* SORT_HPP_ */
