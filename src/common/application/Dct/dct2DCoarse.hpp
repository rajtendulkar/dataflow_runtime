/*
 * dct2DCoarse.hpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef DCT2DCOARSE_HPP_
#define DCT2DCOARSE_HPP_

#include <dctParams.hpp>
#ifdef DCT_APP

class Dct2DCoarse : public ActorExecutor
{
private:
	float coeff[SIZE][SIZE];
public:
	Dct2DCoarse (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId)
	{
		for (int i = 0; i < SIZE; i++)
		{
			float s = (i == 0) ? sqrtf (0.125) : 0.5;
			for (int j = 0; j < SIZE; j++)
				coeff[i][j] = s * cos ((PI / SIZE) * i * (j + 0.5));
		}
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **inputData = (int**)getFifoData(0);
		int **outputData = (int**)getFifoData(1);
        float block_x[SIZE][SIZE];

        for (unsigned int i = 0; i < SIZE; i++)
            for (unsigned int j = 0; j < SIZE; j++)
            {
                block_x[i][j] = 0.0;
                for (unsigned int k = 0; k < SIZE; k++)
                    block_x[i][j] += coeff[j][k] * (*(inputData[SIZE * i + k]));
            }

        for (unsigned int i = 0; i < SIZE; i++)
        {
            for (unsigned int j = 0; j < SIZE; j++)
            {
                float block_y = 0.0;
                for (unsigned int k = 0; k < SIZE; k++)
                    block_y += coeff[i][k] * block_x[k][j];

                block_y = floor (block_y + 0.5);
                *(outputData[i*SIZE+j]) =  ((int) block_y);

            }
        }
	}
};

#endif /* DCT_APP */
#endif /* DCT2DCOARSE_HPP_ */
