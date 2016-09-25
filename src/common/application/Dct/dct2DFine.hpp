/*
 * dct2DFine.hpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef DCT2DFINE_HPP_
#define DCT2DFINE_HPP_

#include <dctParams.hpp>

#ifdef DCT_APP
// Only one actor is required to be used with different rates.
class DCT1DFine : public ActorExecutor
{
private:
	float coeff[SIZE][SIZE];
public:
	DCT1DFine (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId)
	{
		for (int u = 0; u < SIZE; u++)
		{
			float Cu = 1;
			if (u == 0) Cu = 1 / sqrt (2);

			for (int x = 0; x < SIZE; x++)
				coeff[u][x] = 0.5 * Cu * cos (u * PI * (2.0 * x + 1) / (2.0 * SIZE));
		}
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **inputData= (int**)getFifoData(0);
		int **outputData = (int**)getFifoData(1);

        for (int u = 0; u < SIZE; u++)
        {
            float tempsum = 0;
            for (int x = 0; x < SIZE; x++)
                tempsum += *(inputData[x]) * coeff[u][x];

            *(outputData[u]) = (int)tempsum;
        }
	}
};

#endif /* DCT_APP */
#endif /* DCT2DFINE_HPP_ */
