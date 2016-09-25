/*
 * bitonicOutput.hpp
 *
 *  Created on: Jun 19, 2014
 *      Author: maselbas
 */

#ifndef BITONICOUTPUT_HPP_
#define BITONICOUTPUT_HPP_


#include <bitonicSortParams.hpp>

#ifdef BITONIC_SORT

class Printer : public ActorExecutor
{
private:
public:
	Printer (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **data = (int **)getFifoData(0);

		for(int i=0;i<SIZE;i++)
			cout << " " << *(data[i]);
		cout << endl << endl;
	}
};

#endif /*  BITONIC_SORT */

#endif /* BITONICOUTPUT_HPP_ */
