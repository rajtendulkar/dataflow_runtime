/*
 * splitBranche.hpp
 *
 *  Created on: Jun 30, 2014
 *      Author: maselbas
 */

#ifndef SPLITBRANCHE_HPP_
#define SPLITBRANCHE_HPP_

#include <FilterBankParams.hpp>

#ifdef FILTERBANK_APP

class SplitBranche : public ActorExecutor
{
private:
public:
	SplitBranche (Actor *actor) : ActorExecutor(actor){}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){
		float ** dataIn = (float **)getFifoData(0);

		float ** dataSplit1 = (float **)getFifoData(1);
		float ** dataSplit2 = (float **)getFifoData(2);
		float ** dataSplit3 = (float **)getFifoData(3);
		float ** dataSplit4 = (float **)getFifoData(4);
		float ** dataSplit5 = (float **)getFifoData(5);
		float ** dataSplit6 = (float **)getFifoData(6);
		float ** dataSplit7 = (float **)getFifoData(7);
		float ** dataSplit8 = (float **)getFifoData(8);

		//split duplicate
		float val = *(dataIn[0]);
		*(dataSplit1[0]) = val;
		*(dataSplit2[0]) = val;
		*(dataSplit3[0]) = val;
		*(dataSplit4[0]) = val;

		*(dataSplit5[0]) = val;
		*(dataSplit6[0]) = val;
		*(dataSplit7[0]) = val;
		*(dataSplit8[0]) = val;


	}
};

#endif /* FILTERBANK_APP */

#endif /* SPLITBRANCHE_HPP_ */
