/*
 * latticeSource.hpp
 *
 *  Created on: Jan 9, 2014
 *      Author: rajtendulkar
 */

#ifndef LATTICESOURCE_HPP_
#define LATTICESOURCE_HPP_
#include <latticeParams.hpp>

#ifdef LATTICE_APP
class IntSource : public ActorExecutor
{
private:
	float intData[1];

public:
	IntSource (Actor *actor) : ActorExecutor(actor)
	{
		intData[0] = 1.0;
	}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **data = (float**)getFifoData(0);

		*(data[0]) = intData[0];
		intData[0] = 0.0;
	}
};

#endif /* LATTICE_APP */
#endif /* LATTICESOURCE_HPP_ */
