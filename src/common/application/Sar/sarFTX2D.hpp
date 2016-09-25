/*
 * sarFTX2D.hpp
 *
 *  Created on: Jun 23, 2014
 *      Author: maselbas
 */

#ifndef SARFTX2D_HPP_
#define SARFTX2D_HPP_

#include <sarParams.hpp>
#include <FFT.hpp>

#ifdef SAR_APP

class Cftx2d : public ActorExecutor
{
private:
public:
	Cftx2d (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		//consume and produce n*mc = 70080
		complex **dataIn  = (complex **)getFifoData(0);
		complex **dataOut = (complex **)getFifoData(1);
		cout << "\t>>> FTX2D executing ..." << endl;
		/*
		for (int i =0; i < n*mc ; i++){
			cout << "in[" << i << "] at : " << dataIn[i];
			cout << "\t out[" << i << "] at : " << dataOut[i] <<endl;
		}*/

		FTX2D(dataIn, dataOut, n, mc);
		cout << "\t<<< FTX2D done" << endl;

	}


};

#endif /* SAR_APP */


#endif /* SARFTX2D_HPP_ */
