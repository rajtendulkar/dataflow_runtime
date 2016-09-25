/*
 * radixOutput.hpp
 *
 *  Created on: Jan 9, 2014
 *      Author: rajtendulkar
 */

#ifndef RADIXOUTPUT_HPP_
#define RADIXOUTPUT_HPP_
#include <radixSortParams.hpp>

#ifdef RADIX_SORT
class IntPrinter : public ActorExecutor
{
private:
public:
	IntPrinter (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **data = (int**)getFifoData(0);

		for(int i=1;i<SIZE;i++)
			if(*(data[i]) < *(data[i-1]))
				cout << "Data Incorrectly sorted at index " << i << endl;


	}
};

#endif /* RADIX_SORT */



#endif /* RADIXOUTPUT_HPP_ */
