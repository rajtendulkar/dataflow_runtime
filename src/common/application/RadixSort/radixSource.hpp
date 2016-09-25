/*
 * radixSource.hpp
 *
 *  Created on: Jan 9, 2014
 *      Author: rajtendulkar
 */

#ifndef RADIXSOURCE_HPP_
#define RADIXSOURCE_HPP_
#include <radixSortParams.hpp>

#ifdef RADIX_SORT
class IntSource : public ActorExecutor
{
private:
	int intData[SIZE];

public:
	IntSource (Actor *actor) : ActorExecutor(actor)
	{
		intData[0] = 503;
		intData[1] = 87;
		intData[2] = 512;
		intData[3] = 61;
		intData[4] = 908;
        intData[5] = 170;
        intData[6] = 897;
        intData[7] = 275;
        intData[8] = 653;
        intData[9] = 426;
        intData[10] = 154;
        intData[11] = 509;
        intData[12] = 612;
        intData[13] = 677;
        intData[14] = 765;
        intData[15] = 703;
	}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **data = (int**)getFifoData(0);

		for(int i=0;i<SIZE;i++)
			*(data[i]) = intData[i];
	}
};

#endif /* RADIX_SORT */
#endif /* RADIXSOURCE_HPP_ */
