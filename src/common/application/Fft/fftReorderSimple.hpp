/*
 * fftReorderSimple.hpp
 *
 *  Created on: Jan 11, 2014
 *      Author: rajtendulkar
 */

#ifndef FFTREORDERSIMPLE_HPP_
#define FFTREORDERSIMPLE_HPP_

#include <fftParams.hpp>

#ifdef FFT_APP
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
		string name = *(actor->name);
		string index = name.substr(actorNamePrefix.length());
		int indexNum = atoi(index.c_str());

		this->totalData = 2*indexNum;
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **inputData = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);
		int outputCnt = 0;

		for (int i = 0; i < totalData; i += 4)
		{
			*(outputData[outputCnt++]) = *(inputData[i]);
			*(outputData[outputCnt++]) = *(inputData[i+1]);
		}

		for (int i = 2; i < totalData; i += 4)
		{
			*(outputData[outputCnt++]) = *(inputData[i]);
			*(outputData[outputCnt++]) = *(inputData[i+1]);
		}
	}
};

#endif /* FFT_APP */
#endif /* FFTREORDERSIMPLE_HPP_ */
