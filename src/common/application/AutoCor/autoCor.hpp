/*
 * autoCor.hpp
 *
 *  Created on: Jun 17, 2014
 *      Author: maselbas
 */

#ifndef AUTOCOR_HPP_
#define AUTOCOR_HPP_

#include <autoCorParams.hpp>
#include <cluster_defs.hpp>


#ifdef AUTOCOR_APP

#define N 32
#define NLAGS 8


class AutoCor : public ActorExecutor {
private:
public:
	AutoCor(Actor *actor) : ActorExecutor(actor) {}

	void init(unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){

		float **dataSrc = (float**)getFifoData(0);
		float **dataDst = (float**)getFifoData(1);

		for (int lag=0; lag<NLAGS ; lag++){
			float sum = 0;
			for (int i=0;i<N-lag; i++){
				sum += *(dataSrc[i]) * *(dataSrc[i+lag]);

			}
			*(dataDst[lag])=sum;

		}


	}

};

#endif /* AUTOCOR_APP */



#endif /* AUTOCOR_HPP_ */
