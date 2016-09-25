/*
 * merger.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef MERGER_HPP_
#define MERGER_HPP_

#include <mergeSortParams.hpp>

#ifdef MERGE_SORT
class Merger : public ActorExecutor
{
private:
	int N;
public:
	Merger (Actor *actor) : ActorExecutor(actor)
	{
		N = -1;
	}

	~Merger()
	{
	}

	void init (unsigned int instanceId)
	{
		string actorNamePrefix = "Merger";
		string *name = actor->name;
		string index = name->substr(actorNamePrefix.length());
		int indexNum = atoi(index.c_str());

		N = indexNum;
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **inputData = (int**)getFifoData(0);
		int **outputData = (int**)getFifoData(1);

		// initialize indices
		int index1 = 0;
		int index2 = 1;
		int outputCount=0;

		// merge values
		while (index1 < N && index2 < N)
		{
			int val1 = *(inputData[index1]);
			int val2 = *(inputData[index2]);

			if (val1 <= val2)
			{
				*(outputData[outputCount++]) = val1;
				index1 += 2;
			}
			else
			{
				*(outputData[outputCount++]) = val2;
				index2 += 2;
			}
		}

		// merge remainder if one stream dries out
		int leftover = index1 < N ? index1 : index2;
		for (int i = leftover; i < N; i += 2)
			*(outputData[outputCount++]) = *(inputData[i]);
	}
};

#endif /* RADIX_SORT */


#endif /* MERGER_HPP_ */
