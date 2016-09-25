/*
 * idct2DFine.hpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef IDCT2DFINE_HPP_
#define IDCT2DFINE_HPP_

#include <dctParams.hpp>

#ifdef DCT_APP

class Idct1DFine : public ActorExecutor
{
private:
	float coeff[SIZE][SIZE];
public:
	Idct1DFine (Actor *actor) : ActorExecutor(actor)
	{
	}

	void init (unsigned int instanceId)
	{
		for (int x = 0; x < SIZE; x++)
		{
			for (int u = 0; u < SIZE; u++)
			{
				float Cu = 1;
				if (u == 0) Cu = 1 / sqrt (2);
				coeff[x][u] = 0.5 * Cu * cos (u * PI * (2.0 * x + 1) / (2.0 * SIZE));
			}
		}
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **inputData = (int**)getFifoData(0);
		int **outputData = (int**)getFifoData(1);

		for (int x = 0; x < SIZE; x++)
		{
			float tempsum = 0;
			for (int u = 0; u < SIZE; u++)
				tempsum += coeff[x][u] * (*(inputData[u]));

			*(outputData[x]) = (int)tempsum;
		}
	}
};

#endif /* DCT_APP */
#endif /* IDCT2DFINE_HPP_ */
