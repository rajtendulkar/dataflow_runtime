/*
 * splitter.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef SPLITTER_HPP_
#define SPLITTER_HPP_

#include <mergeSortParams.hpp>

#ifdef MERGE_SORT
class InputSplitter : public ActorExecutor
{
private:
	int length;
public:
	InputSplitter (Actor *actor) : ActorExecutor(actor)
	{
		length = -1;
	}

	void init (unsigned int instanceId)
	{
		string actorNamePrefix = "Split";
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
			*(outputData[i/2]) = *(inputData[i]);
			*(outputData[length/2+i/2]) = *(inputData[i+1]);
		}
	}
};

#endif /* MERGE_SORT */


#endif /* SPLITTER_HPP_ */
