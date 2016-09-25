/*
 * blockMultiply.hpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef BLOCKMULTIPLY_HPP_
#define BLOCKMULTIPLY_HPP_

#include <matrixParams.hpp>

#ifdef MATRIX_MULT

class BlockMultiply : public ActorExecutor
{
private:
	int x0, y0, x1, y1;

public:
	BlockMultiply (Actor *actor) : ActorExecutor(actor)
	{
		this->x0 = 0;
		this->x1 = 0;
		this->y0 = 0;
		this->y1 = 0;
	}
	~BlockMultiply() {}


	void init (unsigned int instanceId, int x0, int y0, int x1, int y1)
	{
		this->x0 = x0;
		this->y0 = y0;
		this->x1 = x1;
		this->y1 = y1;
	}

	void init (unsigned int instanceId)
	{
		init (instanceId, X0 / BLOCKDIV, Y0 / BLOCKDIV, X1 / BLOCKDIV, Y1 / BLOCKDIV);
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **inputData = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);

		int block2Start = x0 * y0;

		for (int y = 0; y < y0; y++)
		{
			for (int x = 0; x < x1; x++)
			{
				float sum = 0;
				for (int z = 0; z < x0; z++)
				{
					int leftPos = z + y * x0;
					int rightPos = z + x * y1 + block2Start;
					float left = *(inputData[leftPos]);
					float right = *(inputData[rightPos]);
					sum += left * right;
				}

				*(outputData[y*x1 + x]) = sum;
			}
		}
	}
};

#endif /* MATRIX_MULT */

#endif /* BLOCKMULTIPLY_HPP_ */
