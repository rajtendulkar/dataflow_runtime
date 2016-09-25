/*
 * intSource.hpp
 *
 * 	Created on: Jun 16, 2014
 * 		Author: maselbas
 */

#ifndef INTSOURCE_HPP_
#define INTSOURCE_HPP_

#include <delayParams.hpp>
#include <cluster_defs.hpp>

#ifdef DELAY_APP

static int N = 0;

class IntSource : public ActorExecutor {
private:
public:

	IntSource(Actor *actor) : ActorExecutor(actor) {}

	void init(unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){
		int **data = (int**)getFifoData(0);

		*(data[0]) = N++;
		//cout << "push  :" << *(data[0]) << endl;


	}


};

#endif /* DELAY_APP */

#endif /* INTSOURCE_HPP_ */
