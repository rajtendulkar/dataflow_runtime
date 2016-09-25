/*
 * fftReorder.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef FFTREORDER_HPP_
#define FFTREORDER_HPP_

#include <tdeParams.hpp>

#ifdef TDE_APP
class FftReorder : public ActorExecutor
{
private:
	int totalData;

public:
	FftReorder (Actor *actor) : ActorExecutor(actor)
	{
		totalData = 0;
	}

	~FftReorder()
	{
	}

	void init (unsigned int instanceId)
	{
		string actorNamePrefix = "FftReorder";
		string actorNamePrefix2 = "FftAReorder";
		string *name = actor->name;
		int indexNum = 0;

		if (name->compare(0, actorNamePrefix.length(), actorNamePrefix) == 0)
		{
			string index = name->substr(actorNamePrefix.length());
			indexNum = atoi(index.c_str());
		}
		else if (name->compare(0, actorNamePrefix2.length(), actorNamePrefix2) == 0)
		{
			string index = name->substr(actorNamePrefix2.length());
			indexNum = atoi(index.c_str());
		}
		else
		{
			cout << "initializing illegal for : " << name << endl;
			std::runtime_error("Actor not known.");
		}

		totalData = 2*indexNum;
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{

		float **inputData = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);
		int outputCount = 0;

		for (int i = 0; i < totalData; i+=4)
		{
			*(outputData[outputCount++]) = *(inputData[i]);
			*(outputData[outputCount++]) = *(inputData[i+1]);
		}

		for (int i = 2; i < totalData; i+=4)
		{
			*(outputData[outputCount++]) = *(inputData[i]);
			*(outputData[outputCount++]) = *(inputData[i+1]);
		}
	}
};

#endif /* TDE_APP */
#endif /* FFTREORDER_HPP_ */
