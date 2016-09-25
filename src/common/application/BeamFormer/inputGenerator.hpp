/*
 * inputGenerator.hpp
 *
 *  Created on: Jan 4, 2014
 *      Author: rajtendulkar
 */

#ifndef INPUTGENERATOR_HPP_
#define INPUTGENERATOR_HPP_

#include <iostream>
#include <iomanip>
#include <beamformerParams.hpp>

#ifdef BEAM_FOMER

class InputGenerate : public ActorExecutor
{
private:
	int curSample;
	bool holdsTarget;

public:
	InputGenerate (Actor *actor) : ActorExecutor(actor)
	{
		curSample = 0;
		holdsTarget = 0;
	}

	void init (int myChannel, int numberOfSamples, int tarBeam, int targetSample, float thresh)
	{
		curSample = 0;
		holdsTarget = (tarBeam == myChannel);
	}

	void init (unsigned int instanceId)
	{
		init (instanceId, NUM_SAMPLES, TARGET_BEAM, TARGET_SAMPLE, C_FAR_THRESHOLD);
	}

	void execute (int myChannel, int numberOfSamples, int tarBeam, int targetSample, float thresh, unsigned int iterationId)
	{
		float **data = (float**)getFifoData(0);

		// Should Execute 2 times.
		for(int i=0;i<2;i++)
		{
			if (holdsTarget && (curSample == TARGET_SAMPLE))
			{
				*(data[i*2+0]) =  (sqrt (curSample * myChannel));
				*(data[i*2+1]) =  (sqrt (curSample * myChannel) + 1);
			}
			else
			{
				*(data[i*2+0]) = (-sqrtf (curSample * myChannel));
				*(data[i*2+1]) = (- (sqrtf (curSample * myChannel) + 1));
				// cout << myChannel << " sample 2 " << *(data[i*2+0]) << " " << *(data[i*2+1]) << endl;
			}

			curSample++;

			if (curSample >= NUM_SAMPLES)
				curSample = 0;
		}
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		execute (instanceId, NUM_SAMPLES, TARGET_BEAM, TARGET_SAMPLE, C_FAR_THRESHOLD, iterationId);
	}
};

#endif /* BEAM_FOMER */
#endif /* INPUTGENERATOR_HPP_ */
