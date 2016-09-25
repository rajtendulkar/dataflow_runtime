/*
 * FloatPrinter.hpp
 *
 *  Created on: Jul 18, 2014
 *      Author: maselbas
 */

#ifndef FLOATPRINTER_HPP_
#define FLOATPRINTER_HPP_

#include <LowPassFilterParams.hpp>

#ifdef LPF_APP

class FloatPrinter : public ActorExecutor
{
private:

public:
	FloatPrinter(Actor *actor) : ActorExecutor(actor){}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float ** dataIn = (float **)getFifoData(0);

		//pop 1
		cout << *(dataIn[0]) << endl;
	}
};

#endif /* LPF_APP */

#endif /* FLOATPRINTER_HPP_ */
