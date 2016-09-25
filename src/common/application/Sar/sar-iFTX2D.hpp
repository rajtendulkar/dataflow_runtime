/*
 * sar-iFTX2D.hpp
 *
 *  Created on: Jun 23, 2014
 *      Author: maselbas
 */

#ifndef SAR_IFTX2D_HPP_
#define SAR_IFTX2D_HPP_


#include <sarParams.hpp>
#include <FFT.hpp>

#ifdef SAR_APP
class Ciftx2d : public ActorExecutor
{
private:
public:
	Ciftx2d (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		//consume and produce nx * m = 266 * 382 = 101612
		complex **dataIn  = (complex **)getFifoData(0);
		complex **dataOut = (complex **)getFifoData(1);
		cout << "\t>>> iFTX2D executing ..." << endl;
		iFTX2D(dataIn,dataOut,nx,m);
		cout << "\t<<< iFTX2D done" << endl;

	}


};

#endif /* SAR_APP */

#endif /* SAR_IFTX2D_HPP_ */
