/*
 * outputJoiner.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef JOINER_HPP_
#define JOINER_HPP_

#include <mergeSortParams.hpp>

#ifdef MERGE_SORT
class OutputJoiner : public ActorExecutor
{
private:
	int length;

public:
	OutputJoiner (Actor *actor) : ActorExecutor(actor)
	{
		length = -1;
	}

	void init (unsigned int instanceId)
	{
		string actorNamePrefix = "Join";
		string *name = actor->name;
		string index = name->substr(actorNamePrefix.length());
		int indexNum = atoi(index.c_str());

		length = indexNum;
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **inputData = (int**)getFifoData(0);
		int **outputData = (int**)getFifoData(1);

		for(int i=0;i<length;i+=2)
		{
			*(outputData[i]) = *(inputData[i/2]);
			*(outputData[i+1]) = *(inputData[length/2+i/2]);
		}
	}
};

#endif /* MERGE_SORT */
#endif /* JOINER_HPP_ */
