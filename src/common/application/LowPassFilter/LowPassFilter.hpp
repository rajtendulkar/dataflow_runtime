/*
 * LowPassFilter.hpp
 *
 *  Created on: Jul 18, 2014
 *      Author: maselbas
 */

#ifndef LOWPASSFILTER_HPP_
#define LOWPASSFILTER_HPP_

#include <LowPassFilterParams.hpp>
#include <cmath>
#ifdef LPF_APP

#define TAPS 	64
#define CUTOFF 	1000.0
#define RATE	250000000.0
#define PI		3.14159265359

class LowPassFilter : public ActorExecutor
{
private:
	float coeff[TAPS];
public:
	LowPassFilter (Actor *actor) : ActorExecutor(actor){}

	void init (unsigned int instanceId) {
		float m = TAPS -1;
		float w = 2 * PI * CUTOFF / RATE;
		for(int i=0; i< TAPS ; i++){
			if(i - m / 2 == 0){
				coeff[i] = w / PI;
			}
			else{
				coeff[i] = sin(w * (i - m / 2)) / PI / (i - m / 2) * (0.54 - 0.46 * cos (2 * PI * i / m));
			}
		}
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float ** dataIn  = (float **)getFifoData(0);
		float ** dataOut = (float **)getFifoData(1);

		//pop 1 +2 push 1 peek 64 (TAPS)
		float sum = 0;
		for (int i = 0; i < TAPS; i++)
			sum += *(dataIn[i]) * coeff[i];

		*(dataOut[0]) = sum;
	}
};

#endif /* LPF_APP */

#endif /* LOWPASSFILTER_HPP_ */
