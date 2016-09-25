/*
 * tdeSource.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef TDESOURCE_HPP_
#define TDESOURCE_HPP_

#include <tdeParams.hpp>

#ifdef TDE_APP
class TdeSource : public ActorExecutor
{
private:

public:
	TdeSource (Actor *actor) : ActorExecutor(actor)
	{
	}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		#include <sourceArray.hpp>
		float **data = (float**)getFifoData(0);

		for (int i=0; i<SOURCE_ARRAY_SIZE; i++)
			*(data[i]) = Raw[i];
	}
};

#endif /* TDE_APP */
#endif /* TDESOURCE_HPP_ */
