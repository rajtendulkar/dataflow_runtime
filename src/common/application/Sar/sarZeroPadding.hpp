/*
 * sarZeroPadding.hpp
 *
 *  Created on: Jun 24, 2014
 *      Author: maselbas
 */

#ifndef SARZEROPADDING_HPP_
#define SARZEROPADDING_HPP_

#include <sarParams.hpp>

#ifdef SAR_APP

class ZeroPadding : public ActorExecutor {
private:
public:

	ZeroPadding(Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){

		complex ** dataIn  = (complex **)getFifoData(0);
		complex ** dataOut = (complex **)getFifoData(1);

		cout << "\t>>> ZeroPadding executing ..." << endl;

		/*(int n, int m, int mc)*/

	    int     mz = m - mc;
	    float   q  = (float) m / (float) mc;
	    complex zero={0,0};
	    int k=0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
            	//cout << " k = "<< k << endl;
                if ((j < mz / 2) || ( j >= mc+mz / 2)) {
                    *(dataOut[i*m+j])=zero;
                } else {
                    complex in = *(dataIn[k++]);
                    complex out;
                    out.real = q * in.real;
                    out.imag = q * in.imag;
                    *(dataOut[i*m+j])=out;

                }
            }
        }
		cout << "\t<<< ZeroPadding done" << endl;

	}
};

#endif /* SAR_APP */

#endif /* SARZEROPADDING_HPP_ */
