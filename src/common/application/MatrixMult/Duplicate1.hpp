/*
 * Duplicate.hpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef DUPLICATE1_HPP_
#define DUPLICATE1_HPP_

#include <matrixParams.hpp>

#ifdef MATRIX_MULT

class Duplicate1 : public ActorExecutor
{
private:
	int x,y;

public:
	Duplicate1 (Actor *actor) : ActorExecutor(actor)
	{
		this->x = 0;
		this->y = 0;
	}

	~Duplicate1()
	{

	}

	void init (unsigned int instanceId, int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void init (unsigned int instanceId)
	{
		init (instanceId, X1 * Y1 / BLOCKDIV, BLOCKDIV);
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **inputData = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);

		for(int numBlock=0;numBlock<y;numBlock++)
		{
			for(int i=0;i<x*y;i++)
				*(outputData[(numBlock*x*y) + i]) = *(inputData[i]);
		}
	}
};

#endif /* MATRIX_MULT */
#endif /* DUPLICATE1_HPP_ */
