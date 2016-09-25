/*
 * firFilter.hpp
 *
 *  Created on: Jun 30, 2014
 *      Author: maselbas
 */

#ifndef FIRFILTER_HPP_
#define FIRFILTER_HPP_

#include <FilterBankParams.hpp>

#ifdef FILTERBANK_APP

class FirFilter : public ActorExecutor
{
private:
	float* COEFF;
public:
	FirFilter (Actor *actor, float* arr) : ActorExecutor(actor), COEFF(arr) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){
		float** dataIn  = (float **)getFifoData(0);
		float** dataOut = (float **)getFifoData(1);

		float sum = 0;
		for (int i = 0; i < N_col; i++){
			sum += *(dataIn[i]) * COEFF[N_col - 1 - i];
		}
		*(dataOut[0])=sum;
	}
};

#endif /* FILTERBANK_APP */

#endif /* FIRFILTER_HPP_ */
