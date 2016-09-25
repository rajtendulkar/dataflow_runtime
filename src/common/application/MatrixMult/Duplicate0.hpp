/*
 * Duplicate.hpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef DUPLICATE0_HPP_
#define DUPLICATE0_HPP_

#include <matrixParams.hpp>

#ifdef MATRIX_MULT

class Duplicate0 : public ActorExecutor
{
private:
	int x,y;

public:
	Duplicate0 (Actor *actor) : ActorExecutor(actor)
	{
		this->x = 0;
		this->y = 0;
	}

	~Duplicate0() {}

	void init (unsigned int instanceId, int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void init (unsigned int instanceId)
	{
		init (instanceId, X0 * Y0 / BLOCKDIV, BLOCKDIV);
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **inputData = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);

		for(int i=0;i<y;i++)
			for(int j=0;j<x;j++)
				*(outputData[i*x + j]) = *(inputData[j]);

	}
};

#endif /* MATRIX_MULT */
#endif /* DUPLICATE0_HPP_ */
