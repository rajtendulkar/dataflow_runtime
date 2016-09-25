/*
 * beamForm.hpp
 *
 *  Created on: Jan 6, 2014
 *      Author: rajtendulkar
 */

#ifndef BEAMFORM_HPP_
#define BEAMFORM_HPP_

#include <beamformerParams.hpp>

#ifdef BEAM_FOMER

class BeamForm : public ActorExecutor
{
private:
	float *real_weight;
	float *imag_weight;

public:
	BeamForm (Actor *actor) : ActorExecutor(actor)
	{
		// Reset all the variables.
		real_weight = NULL;
		imag_weight = NULL;
	}

	~BeamForm()
	{
		delete [] real_weight;
		delete [] imag_weight;
	}

	void init (unsigned int instanceId, unsigned int numChannels)
	{
		real_weight = new float [numChannels];
		imag_weight = new float [numChannels];

		for (unsigned int j = 0; j < numChannels; j++)
		{
			int idx = j + 1;

			real_weight[j] = sin (idx) / ( (float) (instanceId + idx));
			imag_weight[j] = cos (idx) / ( (float) (instanceId + idx));
		}
	}

	void init (unsigned int instanceId)
	{
		init (instanceId, NUM_CHANNELS);
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float real_curr = 0;
		float imag_curr = 0;

		float **inputData  = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);


		for (int i = 0; i < NUM_CHANNELS; i++)
		{
			float real_pop = *(inputData[i*2+0]);
			float imag_pop = *(inputData[i*2+1]);
			real_curr += real_weight[i] * real_pop - imag_weight[i] * imag_pop;
			imag_curr += real_weight[i] * imag_pop + imag_weight[i] * real_pop;
		}

		*(outputData[0]) = real_curr;
		*(outputData[1]) = imag_curr;
	}

};
#endif /* BEAM_FOMER */
#endif /* BEAMFORM_HPP_ */
