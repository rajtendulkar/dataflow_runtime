/*
 * source.hpp
 *
 *  Created on: Jun 17, 2014
 *      Author: maselbas
 */

#ifndef SOURCE_HPP_
#define SOURCE_HPP_

#include <autoCorParams.hpp>
#include <cluster_defs.hpp>

#ifdef AUTOCOR_APP

class Source : public ActorExecutor {
private:
public:
	Source(Actor *actor) : ActorExecutor(actor) {}

	void init(unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){

		float **data = (float**)getFifoData(0);

		static float n = 0.0;
		*(data[0]) = n;
		n += 0.01;


		cout << "Push  :" << *(data[0]) << endl;

	}

};

#endif /* AUTOCOR_APP */



#endif /* SOURCE_HPP_ */
