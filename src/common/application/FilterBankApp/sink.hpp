/*
 * sink.hpp
 *
 *  Created on: Jun 30, 2014
 *      Author: maselbas
 */

#ifndef SINK_HPP_
#define SINK_HPP_

#include <FilterBankParams.hpp>

#ifdef FILTERBANK_APP

class Sink : public ActorExecutor
{
private:
public:
	Sink (Actor *actor) : ActorExecutor(actor){}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){
		float** dataIn = (float **)getFifoData(0);

		// cout << "data: " << *(dataIn[0]) << endl;
	}
};

#endif /* FILTERBANK_APP */

#endif /* SINK_HPP_ */
