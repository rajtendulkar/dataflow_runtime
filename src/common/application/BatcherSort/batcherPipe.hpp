/*
 * batcherPipe.hpp
 *
 *  Created on: Jan 11, 2014
 *      Author: rajtendulkar
 */

#ifndef BATCHERPIPE_HPP_
#define BATCHERPIPE_HPP_

#include <batcherSortParams.hpp>

#ifdef BATCHER_SORT
class BatcherPipe : public ActorExecutor
{
private:
public:
	BatcherPipe (Actor *actor) : ActorExecutor(actor) { }

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **inputData = (int**)getFifoData(0);
		int **outputData = (int**)getFifoData(1);

		int p;

		for(p = START; (p > 0) ; p = p / 2)
		{
			int d = p;
			int r = 0;
			int q = START;
			while(1 == 1)
			{
				for(int i=0; i < SIZE - d; i++)
				{
					if ((i & p) == r)
					{
						if (*(inputData[i]) > *(inputData[i + d]))
						{
							int temp = *(inputData[i]);
							*(inputData[i]) = *(inputData[i+d]);
							*(inputData[i+d]) = temp;
						}
					}
				}

				if (p == q)
					break;
				d = q - p;
				q = q/2;
				r = p;
			}
		}

		for(int i=0; i < SIZE; i++)
			*(outputData[i]) = *(inputData[i]);
	}
};

#endif /* BATCHER_SORT */


#endif /* BATCHERPIPE_HPP_ */
