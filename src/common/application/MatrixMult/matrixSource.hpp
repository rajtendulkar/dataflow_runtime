/*
 * matrixSouce.hpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef MATRIXSOURCE_HPP_
#define MATRIXSOURCE_HPP_

#include <matrixParams.hpp>

#ifdef MATRIX_MULT

class MatrixSource : public ActorExecutor
{
private:
	float matrix1[X0][Y0], matrix2[X1][Y1];
public:
	MatrixSource (Actor *actor) : ActorExecutor(actor)
	{
		int count = 0;
		for(int i=0;i<X0;i++)
			for(int j=0;j<Y0;j++)
				matrix1[i][j] =  count++;

		for(int i=0;i<X1;i++)
			for(int j=0;j<Y1;j++)
				matrix2[i][j] =  count++;
	}

	void init (unsigned int instanceId)
	{
#if 0
		cout << "MATRIX 1" << endl;
		for(int i=0;i<X0;i++)
		{
			for(int j=0;j<Y0;j++)
				cout << "\t" << matrix1[i][j];
			cout << endl;
		}

		cout << "MATRIX 2" << endl;
		for(int i=0;i<X1;i++)
		{
			for(int j=0;j<Y1;j++)
				cout << "\t" << matrix2[i][j];
			cout << endl;
		}
#endif
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **data0 = (float**)getFifoData(0);
		float **data1= (float**)getFifoData(1);

		for(int i=0;i<X0;i++)
			for(int j=0;j<Y0;j++)
				*(data0[i*X0 + j]) = matrix1[i][j];

		for(int i=0;i<X1;i++)
			for(int j=0;j<Y1;j++)
				*(data1[i*Y1 + j]) = matrix2[i][j];
	}
};

#endif /* MATRIX_MULT */
#endif /* MATRIXSOURCE_HPP_ */
