/*
 * insertionOutput.hpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#ifndef INSERTIONOUTPUT_HPP_
#define INSERTIONOUTPUT_HPP_

#include <insertionSortParams.hpp>

#ifdef INSERTION_SORT
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

#endif /* INSERTION_SORT */

#endif /* INSERTIONOUTPUT_HPP_ */
