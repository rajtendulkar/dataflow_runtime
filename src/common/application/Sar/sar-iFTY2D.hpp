/*
 * sar-iFTY2D.hpp
 *
 *  Created on: Jun 23, 2014
 *      Author: maselbas
 */

#ifndef SAR_IFTY2D_HPP_
#define SAR_IFTY2D_HPP_

#include <sarParams.hpp>
#include <FFT.hpp>

#ifdef SAR_APP

class Cifty2d : public ActorExecutor
{
private:
	int rows;
	int cols;
public:
	Cifty2d (Actor *actor, int row, int col) : ActorExecutor(actor), rows(row), cols(col){}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		// o-padd -> decompr // consume and produce n * m = 167316 // iFTY2D(n, m)

		// interpol -> iFTX2D (in reconstr) // consume and produce nx * m = 101612  // FTY2D(nx, m)

		complex **dataIn  = (complex **)getFifoData(0);
		complex **dataOut = (complex **)getFifoData(1);
		cout << "\t>>> iFTY2D executing ..." << endl;

		iFTY2D(dataIn, dataOut,rows,cols);
		cout << "\t<<< iFTY2D done" << endl;

	}


};

#endif /*  SAR_APP */


#endif /* SAR_IFTY2D_HPP_ */
