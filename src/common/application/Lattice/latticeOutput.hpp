/*
 * latticeOutput.hpp
 *
 *  Created on: Jan 9, 2014
 *      Author: rajtendulkar
 */

#ifndef LATTICEOUTPUT_HPP_
#define LATTICEOUTPUT_HPP_
#include <latticeParams.hpp>

#ifdef LATTICE_APP
class IntPrinter : public ActorExecutor
{
private:
public:
	IntPrinter (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **data = (float**)getFifoData(0);

		for(int i=0;i<OUTPUT_SIZE;i+=2)
			cout << " " << *(data[i]);
		cout << endl;

	}
};

#endif /* LATTICE_APP */
#endif /* LATTICEOUTPUT_HPP_ */
