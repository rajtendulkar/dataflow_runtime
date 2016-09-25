/*
 * FloatSource.hpp
 *
 *  Created on: Jul 18, 2014
 *      Author: maselbas
 */

#ifndef FLOATSOURCE_HPP_
#define FLOATSOURCE_HPP_

#include <LowPassFilterParams.hpp>

#ifdef LPF_APP

class FloatSource : public ActorExecutor
{
private:

public:
	FloatSource (Actor *actor) : ActorExecutor(actor){}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float ** dataOut = (float **)getFifoData(0);

		//push 1
		*(dataOut[0]) = (float)iterationId * actor->instances +instanceId;
	}
};

#endif /* LPF_APP */

#endif /* FLOATSOURCE_HPP_ */
