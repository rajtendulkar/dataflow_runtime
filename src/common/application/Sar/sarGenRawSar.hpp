/*
 * sarGenRawSar.hpp
 *
 *  Created on: Jun 24, 2014
 *      Author: maselbas
 */

#ifndef SARGENRAWSAR_HPP_
#define SARGENRAWSAR_HPP_

#include <sarParams.hpp>
#include <genRawSar.hpp>

#ifdef SAR_APP

class GenRawSar : public ActorExecutor {
private:
public:
	GenRawSar (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){
		// produce n*mc = 438 * 160 = 70080
		complex ** dataOut = (complex **)getFifoData(0);
		cout << "\t>>> GenRawSar executing ..." << endl;
		genRawSar(dataOut);
		cout << "\t<<< GenRawSar done" << endl;


	}


};

#endif /* SAR_APP */


#endif /* SARGENRAWSAR_HPP_ */
