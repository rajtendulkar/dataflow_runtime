/*
 * combineIdftFinal.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef COMBINEIDFTFINAL_HPP_
#define COMBINEIDFTFINAL_HPP_
#include <tdeParams.hpp>

#ifdef TDE_APP
class CombineIdftFinal : public ActorExecutor
{
private:
	float *w;
	int n;
	float n_recip;

public:
	CombineIdftFinal (Actor *actor) : ActorExecutor(actor)
	{
		n = 0;
		w = NULL;
		n_recip = 0;
	}

	~CombineIdftFinal()
	{
		delete [] w;
	}

	void init (unsigned int instanceId)
	{
		this->n = 64;
		w = new float[n];

		float wn_r = (float)cos(2 * 3.141592654 / n);
		float wn_i = (float)sin(2 * 3.141592654 / n);
		n_recip = 1.0/((float)n);
		// scales coefficients for y1 (but not y0)
		float real = n_recip;
		float imag = 0;
		float next_real, next_imag;
		for (int i=0; i<n; i+=2)
		{
			w[i] = real;
			w[i+1] = imag;
			next_real = real * wn_r - imag * wn_i;
			next_imag = real * wn_i + imag * wn_r;
			real = next_real;
			imag = next_imag;
		}
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **inputData = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);

		for (int i = 0; i < n; i += 2)
		{
			int i_plus_1 = i+1;

			// y0: extra mult to scale
			float y0_r = n_recip * (*(inputData[i]));
			float y0_i = n_recip *  (*(inputData[i_plus_1]));

			float y1_r =  (*(inputData[n + i]));
			float y1_i =  (*(inputData[n + i_plus_1]));

			// load into temps to make sure it doesn't got loaded
			// separately for each load
			float weight_real = w[i];
			float weight_imag = w[i_plus_1];

			float y1w_r = y1_r * weight_real - y1_i * weight_imag;
			float y1w_i = y1_r * weight_imag + y1_i * weight_real;

			*(outputData[i]) = y0_r + y1w_r;
			*(outputData[i + 1]) = y0_i + y1w_i;

			*(outputData[n + i]) = y0_r - y1w_r;
			*(outputData[n + i + 1]) = y0_i - y1w_i;
		}
	}
};

#endif /* TDE_APP */
#endif /* COMBINEIDFTFINAL_HPP_ */
