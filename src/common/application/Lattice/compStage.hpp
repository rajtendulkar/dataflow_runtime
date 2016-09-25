/*
 * compStage.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef COMPSTAGE_HPP_
#define COMPSTAGE_HPP_
#include <latticeParams.hpp>

float last[NUM_COMPSTAGE_ACTORS];

#ifdef LATTICE_APP
// Warning : This is a stateful actor. don't execute in parallel.
class CompStage : public ActorExecutor
{
private:
	float k_par;
	int lastIndex;
public:
	CompStage (Actor *actor) : ActorExecutor(actor)
	{
		k_par = 0.0;
		lastIndex = -1;
	}

	void init (unsigned int instanceId)
	{
		string actorNamePrefix = "CompStage";
		string *name = actor->name;
		string index = name->substr(actorNamePrefix.length());
		int indexNum = atoi(index.c_str());
		lastIndex = indexNum - 2;

		k_par = (float)indexNum;
		last[lastIndex] = 0.0;
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **inputData = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);

		// This is the code of LatDel() filter.
		*(outputData[0]) = *(inputData[0]);
		*(outputData[1]) = last[lastIndex];
		last[lastIndex] = *(inputData[0]);

		// This is the code of LatFlit() filter.
		float e_i = 0;
		float e_bar_i = 0;
		e_i = *(outputData[0]) - k_par * (*(outputData[1]));
		e_bar_i = *(outputData[1]) - k_par * (*(outputData[0]));

		*(outputData[0]) = e_i;
		*(outputData[1]) = e_bar_i;
	}
};

#endif /* LATTICE_APP */
#endif /* COMPSTAGE_HPP_ */
