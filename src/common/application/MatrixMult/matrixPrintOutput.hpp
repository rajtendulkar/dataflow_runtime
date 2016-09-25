/*
 * matrixPrintOutput.hpp
 *
 *  Created on: Jan 8, 2014
 *      Author: rajtendulkar
 */

#ifndef MATRIXPRINTOUTPUT_HPP_
#define MATRIXPRINTOUTPUT_HPP_

#include <matrixParams.hpp>

#ifdef MATRIX_MULT
// Just re-arrange the outputs.
class MatrixPrintOutput : public ActorExecutor
{
private:
public:
	MatrixPrintOutput (Actor *actor) : ActorExecutor(actor) {}
	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
#if 0
		float **inputData = (float**)getFifoData(0);

		cout << "Matrix Output " << endl;
		for(int i=0;i<X0;i++)
		{
			for(int j=0;j<X1;j++)
				cout << "\t" << *(inputData[i*X1+j]);
			cout << endl;
		}
#endif
	}
};

#endif /* MATRIX_MULT */
#endif /* MATRIXPRINTOUTPUT_HPP_ */
