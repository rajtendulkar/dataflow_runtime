/*
 * MatrixJoiner.hpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef MATRIXJOINER_HPP_
#define MATRIXJOINER_HPP_

#include <matrixParams.hpp>

#ifdef MATRIX_MULT

class MatrixJoiner : public ActorExecutor
{
private:
public:
	MatrixJoiner (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **inputData0 = (float**)getFifoData(0);
		float **inputData1 = (float**)getFifoData(1);
		float **outputData = (float**)getFifoData(2);

		for(int i=0;i<(X0*Y0)/(BLOCKDIV*BLOCKDIV);i++)
			*(outputData[i]) = *(inputData0[i]);

		for(int i=0;i<(X1*Y1)/(BLOCKDIV*BLOCKDIV);i++)
			*(outputData[(X0*Y0)/(BLOCKDIV*BLOCKDIV)+i]) = *(inputData1[i]);
	}
};

#endif /* MATRIX_MULT */
#endif /* MATRIXJOINER_HPP_ */
