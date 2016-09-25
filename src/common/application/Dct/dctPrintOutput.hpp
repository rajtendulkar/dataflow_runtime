/*
 * dctPrintOutput.hpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef DCTPRINTOUTPUT_HPP_
#define DCTPRINTOUTPUT_HPP_

#include <dctParams.hpp>

#ifdef DCT_APP
// Just re-arrange the outputs.
class DctPrintOutput : public ActorExecutor
{
private:
public:
	DctPrintOutput (Actor *actor) : ActorExecutor(actor) {}
	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
#if 0
		int **inputData = (int **)getFifoData(0);

		for(unsigned int i=0;i<SIZE*SIZE;i++)
				cout << "I : " << i << " : " << *(inputData[i]) << endl;
#endif
	}
};

#endif /* DCT_APP */
#endif /* DCTPRINTOUTPUT_HPP_ */
