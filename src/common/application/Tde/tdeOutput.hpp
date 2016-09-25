/*
 * tdeOutput.hpp
 *
 *  Created on: Jan 9, 2014
 *      Author: rajtendulkar
 */

#ifndef TDEOUTPUT_HPP_
#define TDEOUTPUT_HPP_
#include <tdeParams.hpp>

#ifdef TDE_APP
class FloatPrinter : public ActorExecutor
{
private:
public:
	FloatPrinter (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **data = (float**)getFifoData(0);

		for(int i=0;i<SOURCE_ARRAY_SIZE;i++)
			cout << i << " " << *(data[i]) << endl;
		cout << endl;
	}
};

#endif /* TDE_APP */
#endif /* TDEOUTPUT_HPP_ */
