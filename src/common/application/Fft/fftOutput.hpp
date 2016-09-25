/*
 * dctPrintOutput.hpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef FFTOUTPUT_HPP_
#define FFTOUTPUT_HPP_

#include <fftParams.hpp>

#ifdef FFT_APP
// Just re-arrange the outputs.
class FftOutput : public ActorExecutor
{
private:
public:
	FftOutput (Actor *actor) : ActorExecutor(actor) {}
	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
#if 0
		float **inputData = (float**)getFifoData(0);

		for(unsigned int i=0;i<N*2;i++)
			cout << "output at index " << i << " : " << *(inputData[i]) << endl;
#endif
	}
};

#endif /* FFT_APP */
#endif /* FFTOUTPUT_HPP_ */
