/*
 * idct2DCoarse.hpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef IDCT2DCOARSE_HPP_
#define IDCT2DCOARSE_HPP_

#include <dctParams.hpp>

#ifdef DCT_APP

class Idct2DCoarse : public ActorExecutor
{
private:
	float coeff[SIZE][SIZE];
public:
	Idct2DCoarse (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId)
	{
		for (int freq = 0; freq < SIZE; freq++)
		{
			float scale = (freq == 0) ? sqrt (0.125) : 0.5;
			for (int time = 0; time < SIZE; time++)
				coeff[freq][time] = scale * cos ( (PI / (float) SIZE) * freq * (time + 0.5));
		}
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float block_x[SIZE][SIZE];

		int **inputData =(int**)getFifoData(0);
		int **outputData =(int**)getFifoData(1);

		for (unsigned int i = 0; i < SIZE; i++)
			for (unsigned int j = 0; j < SIZE; j++)
			{
				block_x[i][j] = 0;
				for (unsigned int k = 0; k < SIZE; k++)
				{
					block_x[i][j] += coeff[k][j] * (*(inputData [SIZE * i + k /* that is buffer[i][k] */]));
				}
			}

		for (unsigned int i = 0; i < SIZE; i++)
		{
			for (unsigned int j = 0; j < SIZE; j++)
			{
				float block_y = 0.0;
				for (unsigned int k = 0; k < SIZE; k++)
					block_y += coeff[k][i] * block_x[k][j];
				block_y = floor (block_y + 0.5);
				*(outputData[i*SIZE+j]) = (int)block_y;
			}
		}
	}
};

#endif /* DCT_APP */
#endif /* IDCT2DCOARSE_HPP_ */
