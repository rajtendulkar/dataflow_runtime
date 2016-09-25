/*
 * source.hpp
 *
 *  Created on: Jul 9, 2014
 *      Author: maselbas
 */

#ifndef SOURCE_HPP_
#define SOURCE_HPP_

#include <movingAverageParams.hpp>

#ifdef MOVINGAVERAGE_APP

class Source : public ActorExecutor
{
private:

public:
	Source (Actor *actor) : ActorExecutor(actor){}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		//push 1
		int ** dataOut = (int **)getFifoData(0);
		static int x = 0;
		//cout << "source : " << x << endl;
		*(dataOut[0])=x++;

	}
};

#endif /* MOVINGAVERAGE_APP */


#endif /* SOURCE_HPP_ */
