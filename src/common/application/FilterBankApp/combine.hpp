/*
 * combine.hpp
 *
 *  Created on: Jul 1, 2014
 *      Author: maselbas
 */

#ifndef COMBINE_HPP_
#define COMBINE_HPP_

#include <FilterBankParams.hpp>

#ifdef FILTERBANK_APP

class Combine : public ActorExecutor
{
private:
public:
	Combine (Actor *actor) : ActorExecutor(actor){}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){
		float** dataIn  = (float **)getFifoData(0);
		float** dataOut = (float **)getFifoData(1);

		float sum = 0;
		for (int i = 0; i < N_samp; i++)
			sum += *(dataIn[i]);
		*(dataOut[0])=sum;

	}
};


#endif /* FILTERBANK_APP */


#endif /* COMBINE_HPP_ */
