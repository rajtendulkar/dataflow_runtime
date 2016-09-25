/*
 * radixOutput.hpp
 *
 *  Created on: Jan 9, 2014
 *      Author: rajtendulkar
 */

#ifndef BATCHEROUTPUT_HPP_
#define BATCHEROUTPUT_HPP_
#include <batcherSortParams.hpp>

#ifdef BATCHER_SORT
class IntPrinter : public ActorExecutor
{
private:
public:
	IntPrinter (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **data = (int **)getFifoData(0);

		for(int i=0;i<SIZE;i++)
			cout << " " << *(data[i]);
		cout << endl;
	}
};

#endif /* BATCHER_SORT */
#endif /* BATCHEROUTPUT_HPP_ */
