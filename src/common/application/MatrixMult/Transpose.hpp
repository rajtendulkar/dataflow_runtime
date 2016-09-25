/*
 * Transpose.hpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef TRANSPOSE_HPP_
#define TRANSPOSE_HPP_

#include <matrixParams.hpp>

#ifdef MATRIX_MULT

class Transpose : public ActorExecutor
{
private:
	int x,y;

public:
	Transpose (Actor *actor) : ActorExecutor(actor)
	{
		this->x = 0;
		this->y = 0;
	}
	~Transpose()
	{
	}

	void init (unsigned int instanceId, int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void init (unsigned int instanceId)
	{
		init (instanceId, X1, Y1);
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{

		float **inputData = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);

		for(int i=0;i<y;i++)
			for(int j=0;j<x;j++)
				*(outputData[i*x+j]) = *(inputData[j*y+i]);
	}
};

#endif /* MATRIX_MULT */
#endif /* TRANSPOSE_HPP_ */
