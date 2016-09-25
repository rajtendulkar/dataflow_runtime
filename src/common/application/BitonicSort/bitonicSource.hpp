/*
 * bitonicSource.hpp
 *
 *  Created on: Jun 19, 2014
 *      Author: maselbas
 */

#ifndef BITONICSOURCE_HPP_
#define BITONICSOURCE_HPP_


#include <bitonicSortParams.hpp>

#ifdef BITONIC_SORT

class Source : public ActorExecutor {
private:
	int intData[SIZE];
public:
	Source (Actor *actor) : ActorExecutor(actor){

	}

	void init (unsigned int instanceId) {
		intData[0]  = 503;
		intData[1]  = 789;
		intData[2]  = 512;
		intData[3]  = 061;
		intData[4]  = 908;
		intData[5]  = 170;
		intData[6]  = 897;
		intData[7]  = 275;
		intData[8]  = 653;
		intData[9]  = 426;
		intData[10] = 154;
		intData[11] = 509;
		intData[12] = 612;
		intData[13] = 101;
		intData[14] = 765;
		intData[15] = 703;
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		int **data = (int**)getFifoData(0);
		cout << "------------- " << iterationId << " -------------"<< endl;
		for(int i=0;i<SIZE;i++)
			cout << " " << (*(data[i]) = intData[i]); //print the value of the affectation

		cout << endl;
	}



};

#endif /*  BITONIC_SORT */


#endif /* BITONICSOURCE_HPP_ */
