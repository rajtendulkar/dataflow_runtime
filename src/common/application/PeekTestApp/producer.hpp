/*
 * producer.hpp
 *
 *  Created on: Jul 2, 2014
 *      Author: maselbas
 */

#ifndef PRODUCER_HPP_
#define PRODUCER_HPP_

#include <peekParams.hpp>

#ifdef PEEK_APP

class Producer : public ActorExecutor
{
private:

public:
	Producer (Actor *actor) : ActorExecutor(actor){}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int ** dataOut = (int **)getFifoData(0);

		//push 4
		for (int i = 0 ; i < 4; i++){
			*(dataOut[i]) = iterationId;
			//cout << "push :" << *(dataOut[i]) << endl;
		}


	}
};

#endif /* PEEK_APP */

#endif /* PRODUCER_HPP_ */
