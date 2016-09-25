/*
 * bitonicPipe.hpp
 *
 *  Created on: Jun 19, 2014
 *      Author: maselbas
 */

#ifndef BITONICPIPE_HPP_
#define BITONICPIPE_HPP_

#include <bitonicSortParams.hpp>

#ifdef BITONIC_SORT

#define ASCENDING  true
#define DESCENDING false

class BitonicPipe : public ActorExecutor
{
private:
	int data[SIZE];


	void compare(int i, int j, bool dir){

		if(dir == (data[i]> data[j])){
			int tmp = data[i];
			data[i] = data[j];
			data[j] = tmp;
		}
	}

	void merge_up(int n){
		int step= n/2, i, j, k;
		while(step > 0){
			for(i=0; i<n ; i+=step*2){
				for(j=i, k=0; k<step; j++, k++){
					compare(j,j+step,ASCENDING);
				}
				data[i] = *(inputData[i]);
			}

			for(int s = 2; s<= SIZE; s*=2){
				for(int i=0; i< SIZE; i+= s*2){
					merge_up(s);
					merge_down(s);

			}
			step /= 2;
		}
	}

	void merge_down(int n){
		int step= n/2, i, j, k;
		while(step > 0){
			for(i=0; i<n ; i+=step*2){
				for(j=i, k=0; k<step; j++, k++){
					compare(j+n,j+step+n,DESCENDING);
				}
			}
			step /= 2;
		}
	}



public:
	BitonicPipe (Actor *actor) : ActorExecutor(actor) { }

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){
		int ** inputData = (int**)getFifoData(0);
		int ** outputData = (int**)getFifoData(1);

		for(int i=0; i< SIZE; i++){
			data[i] = *(inputData[i]);
		}

		for(int s = 2; s<= SIZE; s*=2){
			for(int i=0; i< SIZE; i+= s*2){
				merge_up(s);
				merge_down(s);
			}
		}

		for(int i=0; i< SIZE; i++){
			*(outputData[i]) = data[i];
		}
	}

};

#endif /*  BITONIC_SORT */


#endif /* BITONICPIPE_HPP_ */
