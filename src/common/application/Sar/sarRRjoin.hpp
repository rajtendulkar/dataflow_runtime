/*
 * sarRRjoin.hpp
 *
 *  Created on: Jun 24, 2014
 *      Author: maselbas
 */

#ifndef SARRRJOIN_HPP_
#define SARRRJOIN_HPP_

#ifdef SAR_APP

class RRjoin : public ActorExecutor {
private:
public:
	RRjoin (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){
		// produce n*mc = 438 * 160 = 70080
		// consume n+n*mc = 438 + 438 * 160 = 70518

		complex ** dataIn1 = (complex **)getFifoData(0);	//complex[n*mc]; genRawSar
		complex ** dataIn2 = (complex **)getFifoData(1);	//complex[n]; fastfilter
		complex ** dataOut = (complex **)getFifoData(2);   // n*mc


		/* join round robin (1,mc) *//*
		int j=0;
		for(int i=0; i<n; i++){
			*(dataOut[i*mc+j])= *(data2[i]);
			for(j=0; j<mc; j++){
				*(dataOut[1+ i*mc+j]) = *(data1[i*mc+j]);
			}
		}*/

		cout << "\t>>> JoinFilter executing ..." << endl;

		/* join and filter at the same time*/
		for (int i = 0; i < n; i++) {
			complex ftf = *(dataIn2[i]);
			for (int j = 0; j < mc; j++) {
				complex s   = *(dataIn1[i*mc+j]);
				complex out;

				out.real = s.real * ftf.real - s.imag * ftf.imag;
				out.imag = s.imag * ftf.real + s.real * ftf.imag;

				*(dataOut[i*mc+j])=out;
			}
		}

		cout << "\t<<< JoinFilter done" << endl;


	}

};

#endif /* SAR_APP */

#endif /* SARRRJOIN_HPP_ */
