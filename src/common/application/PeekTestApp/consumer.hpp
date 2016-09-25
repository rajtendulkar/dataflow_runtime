/*
 * consumer.hpp
 *
 *  Created on: Jul 2, 2014
 *      Author: maselbas
 */

#ifndef CONSUMER_HPP_
#define CONSUMER_HPP_

#include <peekParams.hpp>
#include <unistd.h>

#ifdef PEEK_APP


class Consumer : public ActorExecutor
{
private:

public:
	Consumer (Actor *actor) : ActorExecutor(actor){}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		// pop 1 peek 4
		int ** dataIn = (int **)getFifoData(0);

		//to test mutual exclusion on data
		//sleep(*(dataIn[0]));

		int sum = 0;
		for (int i=0; i < 4; i++){
			sum += *(dataIn[i]);
		}
		cout << "sum = " << sum << endl;
	}
};

#endif /* PEEK_APP */


#endif /* CONSUMER_HPP_ */
