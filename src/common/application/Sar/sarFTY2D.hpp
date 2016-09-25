/*
 * sarFTY2D.hpp
 *
 *  Created on: Jun 23, 2014
 *      Author: maselbas
 */

#ifndef SARFTY2D_HPP_
#define SARFTY2D_HPP_

#include <sarParams.hpp>
#include <FFT.hpp>

#ifdef SAR_APP

class Cfty2d : public ActorExecutor
{
private:
	int rows;
	int cols;
public:
	Cfty2d (Actor *actor, int row, int col) : ActorExecutor(actor), rows(row), cols(col) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		// comp -> o-padd // consume and produce n * mc = 70080 // FTY2D(n, mc)

		// decomp -> reconst // consume and produce n * m = 167316 // FTY2D(n, m)

		complex **dataIn  = (complex **)getFifoData(0);
		complex **dataOut = (complex **)getFifoData(1);
		cout << "\t>>> FTY2D executing ..." << endl;

		FTY2D(dataIn,dataOut,rows, cols);
		cout << "\t<<< FTY2D done" << endl;


	}


};


#endif /* SAR_APP */

#endif /* SARFTY2D_HPP_ */
