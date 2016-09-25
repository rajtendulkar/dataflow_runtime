/*
 * detector.hpp
 *
 *  Created on: Jan 6, 2014
 *      Author: rajtendulkar
 */

#ifndef DETECTOR_HPP_
#define DETECTOR_HPP_

#include <beamformerParams.hpp>

#ifdef BEAM_FOMER

class Detector : public ActorExecutor
{
private:
	int curSample;
	int myBeam;
	bool holdsTarget;
	float thresh;

	// Store some variables;
	int targetSample;

public:
	Detector (Actor *actor) : ActorExecutor(actor)
	{
		curSample = 0;
		holdsTarget = 0;
		targetSample = 0;
		thresh = 0.0;
		myBeam = 0;
	}

	void init (int instanceId, int _myBeam, int numSamples, int targetBeam, int targetSample, float cfarThreshold)
	{
		curSample = 0;
		holdsTarget = (_myBeam == targetBeam);
		myBeam = _myBeam + 1;
		thresh = 0.1;

		this->targetSample = targetSample;
	}

	void init (unsigned int instanceId)
	{
		init (instanceId, instanceId, NUM_SAMPLES, TARGET_BEAM, TARGET_SAMPLE_POST_DEC, C_FAR_THRESHOLD);
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **inputData = (float**)getFifoData(0);

		float inputVal = *(inputData[0]);
		float outputVal;
		if (holdsTarget && targetSample == curSample)
		{
			if (! (inputVal >= thresh))
				outputVal = 0;
			else
				outputVal = myBeam;
		}
		else
		{
			if (! (inputVal >= thresh))
				outputVal = 0;
			else
				outputVal = -myBeam;
		}

		outputVal = inputVal;
		// cout <<  "output : "  << outputVal << endl;
		curSample++;

		if (curSample >= NUM_SAMPLES)
			curSample = 0;
	}
};

#endif /* BEAM_FOMER */
#endif /* DETECTOR_HPP_ */
