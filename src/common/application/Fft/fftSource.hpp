/*
 * fftSource.hpp
 *
 *  Created on: Jan 11, 2014
 *      Author: rajtendulkar
 */

#ifndef FFTSOURCE_HPP_
#define FFTSOURCE_HPP_

#include <fftParams.hpp>

#ifdef FFT_APP
class FFTTestSource : public ActorExecutor
{
private:
public:
	FFTTestSource (Actor *actor) : ActorExecutor(actor) {}


	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **data = (float**)getFifoData(0);

		*(data[0]) = 0.0;
		*(data[1]) = 0.0;
		*(data[2]) = 1.0;
		*(data[3]) = 0.0;

		for(int i=4;i<2*N;i++)
			*(data[i]) = 0.0;
	}
};

#endif /* FFT_APP */
#endif /* FFTSOURCE_HPP_ */
