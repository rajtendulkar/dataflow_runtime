/*
 * magnitude.hpp
 *
 *  Created on: Jan 6, 2014
 *      Author: rajtendulkar
 */

#ifndef MAGNITUDE_HPP_
#define MAGNITUDE_HPP_

#include <beamformerParams.hpp>

#ifdef BEAM_FOMER

class Magnitude : public ActorExecutor
{
private:

public:
	Magnitude (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **inputData = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);

		*(outputData[0]) = sqrt (*(inputData[0]) * *(inputData[0]) + *(inputData[1]) * *(inputData[1]));
	}
};

#endif /* BEAM_FOMER */
#endif /* MAGNITUDE_HPP_ */
