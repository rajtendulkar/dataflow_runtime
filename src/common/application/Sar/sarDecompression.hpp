/*
 * sarDecompression.hpp
 *
 *  Created on: Jun 24, 2014
 *      Author: maselbas
 */

#ifndef SARDECOMPRESSION_HPP_
#define SARDECOMPRESSION_HPP_

#include <sarParams.hpp>
#include <utils.hpp>

#ifdef SAR_APP

class Decompression : public ActorExecutor {
private:
public:
	Decompression (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){

		complex **dataIn = (complex**)getFifoData(0);
		complex **dataOut= (complex**)getFifoData(1);

		cout << "\t>>> decompression executing ..." << endl;

		decompression(dataIn, dataOut);
		cout << "\t<<< decompression done" << endl;


	}

};

#endif /* SAR_APP */

#endif /* SARDECOMPRESSION_HPP_ */
