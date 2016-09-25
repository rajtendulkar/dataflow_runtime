/*
 * source.hpp
 *
 *  Created on: Jun 30, 2014
 *      Author: maselbas
 */

#ifndef SOURCE_HPP_
#define SOURCE_HPP_

#include <FilterBankParams.hpp>

#ifdef FILTERBANK_APP


class Source : public ActorExecutor
{
private:
public:
	Source (Actor *actor) : ActorExecutor(actor){}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){

		float** dataOut = (float **)getFifoData(0);
		*(dataOut[0]) = (float)((iterationId * actor->instances +instanceId)%1000);

	}
};

#endif /* FILTERBANK */

#endif /* SOURCE_HPP_ */
