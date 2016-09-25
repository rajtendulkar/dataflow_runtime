/*
 * joinBranche.hpp
 *
 *  Created on: Jun 30, 2014
 *      Author: maselbas
 */

#ifndef JOINBRANCHE_HPP_
#define JOINBRANCHE_HPP_

#include <FilterBankParams.hpp>

#ifdef FILTERBANK_APP

class JoinBranche : public ActorExecutor
{
private:
public:
	JoinBranche (Actor *actor) : ActorExecutor(actor){}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){
		float ** dataOut = (float **)getFifoData(0);

		float ** dataJoin1 = (float **)getFifoData(1);
		float ** dataJoin2 = (float **)getFifoData(2);
		float ** dataJoin3 = (float **)getFifoData(3);
		float ** dataJoin4 = (float **)getFifoData(4);
		float ** dataJoin5 = (float **)getFifoData(5);
		float ** dataJoin6 = (float **)getFifoData(6);
		float ** dataJoin7 = (float **)getFifoData(7);
		float ** dataJoin8 = (float **)getFifoData(8);

		//join RoundRobin
		*(dataOut[0]) = *(dataJoin1[0]);
		*(dataOut[1]) = *(dataJoin2[0]);
		*(dataOut[2]) = *(dataJoin3[0]);
		*(dataOut[3]) = *(dataJoin4[0]);

		*(dataOut[4]) = *(dataJoin5[0]);
		*(dataOut[5]) = *(dataJoin6[0]);
		*(dataOut[6]) = *(dataJoin7[0]);
		*(dataOut[7]) = *(dataJoin8[0]);


	}
};

#endif /* FILTERBANK_APP */

#endif /* JOINBRANCHE_HPP_ */
