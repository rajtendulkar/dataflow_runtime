/*
 * radixOutput.hpp
 *
 *  Created on: Jan 9, 2014
 *      Author: rajtendulkar
 */

#ifndef CCOUTPUT_HPP_
#define CCOUTPUT_HPP_

#include <ccParams.hpp>

#ifdef COMPARISON_COUNTING
class IntPrinter : public ActorExecutor
{
private:
public:
	IntPrinter (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **data = (int**)getFifoData(0);
		int expectedOutput[] = {61,87,154,170,275,426,503,509,512,612,653,677,703,765,897,908};

		for(int i=0;i<SIZE;i++)
			if(*data[i] != expectedOutput[i])
				cout << "Output doesn't match at index : " << i << " " << *(data[i]) << endl;
	}
};

#endif /* COMPARISON_COUNTING */
#endif /* CCOUTPUT_HPP_ */
