/*
 * beamformerduplicator.hpp
 *
 *  Created on: Jan 6, 2014
 *      Author: rajtendulkar
 */

#ifndef BEAMFORMERDUPLICATOR_HPP_
#define BEAMFORMERDUPLICATOR_HPP_

#include <beamformerParams.hpp>

#ifdef BEAM_FOMER

class Duplicator : public ActorExecutor
{
public :
	Duplicator (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **inputData = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);

		for(unsigned int j=0;j<NUMBEAMS;j++)
		{
			for(unsigned int i=0;i<NUM_CHANNELS;i++)
			{
				*(outputData[j*NUM_CHANNELS*2 + i*2 + 0]) = *(inputData[i*2 + 0]);
				*(outputData[j*NUM_CHANNELS*2 + i*2 + 1]) = *(inputData[i*2 + 1]);
			}
		}
	}
};

#endif /* BEAM_FOMER */
#endif /* BEAMFORMERDUPLICATOR_HPP_ */
