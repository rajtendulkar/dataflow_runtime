/*
 * sarCompression.hpp
 *
 *  Created on: Jun 24, 2014
 *      Author: maselbas
 */

#ifndef SARCOMPRESSION_HPP_
#define SARCOMPRESSION_HPP_

#include <sarParams.hpp>
#include <utils.hpp>

#ifdef SAR_APP

class Compression : public ActorExecutor {
private:
public:
	Compression (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){
		// consume n*mc = 438 * 160 = 70080
		// produce n*mc
		complex **dataIn = (complex**)getFifoData(0);
		complex **dataOut= (complex**)getFifoData(1);
		cout << "\t>>> compression executing ..." << endl;
		compression(dataIn, dataOut);
		cout << "\t<<< compression done" << endl;


	}

};

#endif /* SAR_APP */

#endif /* SARCOMPRESSION_HPP_ */
