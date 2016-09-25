/*
 * zeroStage.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef ZEROSTAGE_HPP_
#define ZEROSTAGE_HPP_

#include <latticeParams.hpp>

#ifdef LATTICE_APP
class ZeroStage : public ActorExecutor
{
private:

public:
	ZeroStage (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **inputData = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);

		// Just Duplicate the data.
		*(outputData[0]) = *(inputData[0]);
		*(outputData[1]) = *(inputData[0]);
	}
};

#endif /* LATTICE_APP */
#endif /* ZEROSTAGE_HPP_ */
