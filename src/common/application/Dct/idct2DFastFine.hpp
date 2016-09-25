/*
 * idct2DFastFine.hpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef IDCT2DFASTFINE_HPP_
#define IDCT2DFASTFINE_HPP_

#include <dctParams.hpp>

#ifdef DCT_APP

class Idct1DColFastFine : public ActorExecutor
{
private:
	int W1, W2, W3, W5, W6, W7;
public:
	Idct1DColFastFine (Actor *actor) : ActorExecutor(actor)
	{
		W1 = 2841; /* 2048*sqrt(2)*cos(1*pi/16) */
		W2 = 2676; /* 2048*sqrt(2)*cos(2*pi/16) */
		W3 = 2408; /* 2048*sqrt(2)*cos(3*pi/16) */
		W5 = 1609; /* 2048*sqrt(2)*cos(5*pi/16) */
		W6 = 1108; /* 2048*sqrt(2)*cos(6*pi/16) */
		W7 = 565;  /* 2048*sqrt(2)*cos(7*pi/16) */
	}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **inputData = (int**)getFifoData(0);
		int **outputData = (int**)getFifoData(1);

		int x0 = *(inputData[0]);
		int x1 = *(inputData[4]) << 8;
		int x2 = *(inputData[6]);
		int x3 = *(inputData[2]);
		int x4 = *(inputData[1]);
		int x5 = *(inputData[7]);
		int x6 = *(inputData[5]);
		int x7 = *(inputData[3]);
		int x8;

		/* shortcut */
		if ( (x1 == 0) && (x2 == 0) && (x3 == 0) && (x4 == 0) && (x5 == 0) && (x6 == 0) && (x7 == 0))
		{
			x0 = (x0 + 32) >> 6;
			for (int i = 0; i < SIZE; i++)
				*(outputData[i]) =  (x0);
		}
		else
		{
			/* for proper rounding in the fourth stage */
			x0 = (x0 << 8) + 8192;

			/* first stage */
			x8 = W7 * (x4 + x5) + 4;
			x4 = (x8 + (W1 - W7) * x4) >> 3;
			x5 = (x8 - (W1 + W7) * x5) >> 3;
			x8 = W3 * (x6 + x7) + 4;
			x6 = (x8 - (W3 - W5) * x6) >> 3;
			x7 = (x8 - (W3 + W5) * x7) >> 3;

			/* second stage */
			x8 = x0 + x1;
			x0 = x0 - x1;
			x1 = W6 * (x3 + x2) + 4;
			x2 = (x1 - (W2 + W6) * x2) >> 3;
			x3 = (x1 + (W2 - W6) * x3) >> 3;
			x1 = x4 + x6;
			x4 = x4 - x6;
			x6 = x5 + x7;
			x5 = x5 - x7;

			/* third stage */
			x7 = x8 + x3;
			x8 = x8 - x3;
			x3 = x0 + x2;
			x0 = x0 - x2;
			x2 = (181 * (x4 + x5) + 128) >> 8;
			x4 = (181 * (x4 - x5) + 128) >> 8;

			/* fourth stage */
			*(outputData[0]) =   ( (x7 + x1) >> 14);
			*(outputData[1]) =   ( (x3 + x2) >> 14);
			*(outputData[2]) =   ( (x0 + x4) >> 14);
			*(outputData[3]) =   ( (x8 + x6) >> 14);
			*(outputData[4]) =   ( (x8 - x6) >> 14);
			*(outputData[5]) =   ( (x0 - x4) >> 14);
			*(outputData[6]) =   ( (x3 - x2) >> 14);
			*(outputData[7]) =   ( (x7 - x1) >> 14);
		}
	}
};

#endif /* DCT_APP */
#endif /* IDCT2DFASTFINE_HPP_ */
