/*
 * blockAdd.hpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef BLOCKADD_HPP_
#define BLOCKADD_HPP_

#include <matrixParams.hpp>

#ifdef MATRIX_MULT

class BlockAdd : public ActorExecutor
{
private:
	int x,y,times;

public:
	BlockAdd (Actor *actor) : ActorExecutor(actor)
	{
		this->x = 0;
		this->y = 0;
		this->times = 0;
	}
	~BlockAdd()
	{
	}

	void init (unsigned int instanceId, int x, int y, int times)
	{
		this->x = x;
		this->y = y;
		this->times = times;
	}

	void init (unsigned int instanceId)
	{
		init (instanceId, X1 / BLOCKDIV, Y0 / BLOCKDIV, BLOCKDIV);
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **inputData = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);

		 for (int b = 0; b < y; b++)
			for (int a = 0; a < x; a++)
				*(outputData[b*x + a]) = *(inputData[b*x + a]);

		for (int c = 1; c < times; c++)
			for (int b = 0; b < y; b++)
				for (int a = 0; a < x; a++)
					 *(outputData[b*x+a]) += *(inputData[c*x*y + b*x + a]);
	}
};

#endif /* MATRIX_MULT */


#endif /* BLOCKADD_HPP_ */
