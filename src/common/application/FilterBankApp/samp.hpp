/*
 * Samp.hpp
 *
 *  Created on: Jun 30, 2014
 *      Author: maselbas
 */

#ifndef SAMP_HPP_
#define SAMP_HPP_

#include <FilterBankParams.hpp>

#ifdef FILTERBANK_APP

class Samp : public ActorExecutor
{
private:
public:
	Samp (Actor *actor) : ActorExecutor(actor){}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){
		float ** dataIn  = (float**)getFifoData(0);
		float ** dataOut = (float**)getFifoData(1);

		*(dataOut[0]) = *(dataIn[0]);
		for (int i=1; i < N_samp ; i++){
			*(dataOut[i]) = 0.0;
		}

	}
};

#endif /* FILTERBANK_APP */

#endif /* SAMP_HPP_ */
