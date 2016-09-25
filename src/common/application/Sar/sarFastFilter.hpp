/*
 * sarFastFilter.hpp
 *
 *  Created on: Jun 24, 2014
 *      Author: maselbas
 */

#ifndef SARFASTFILTER_HPP_
#define SARFASTFILTER_HPP_

#include <sarParams.hpp>
#include <genRawSar.hpp>

#ifdef SAR_APP

class FastFilter : public ActorExecutor {
private:
public:
	FastFilter (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){
		//produce n = 438
		complex ** dataOut = (complex **)getFifoData(0);

		cout << "\t>>> FastFilter executing ..." << endl;

		FastTimeFilter(dataOut);
		cout << "\t<<< FastFilter done." << endl;


	}

};

#endif /* SAR_APP */

#endif /* SARFASTFILTER_HPP_ */
