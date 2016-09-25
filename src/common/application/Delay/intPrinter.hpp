/*
 * intPrinter.hpp
 *
 * 	Created on: Jun 16, 2014
 * 		Author: maselbas
 */


#ifndef INTPRINTER_HPP_
#define INTPRINTER_HPP_

#include <delayParams.hpp>
#include <cluster_defs.hpp>

#ifdef DELAY_APP

class IntPrinter : public ActorExecutor {
private:
public:
	IntPrinter(Actor *actor) : ActorExecutor(actor) {}

	void init(unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){

		int **data = (int**)getFifoData(0);

		cout << "Data  :" << *(data[0]) << endl;

	}

};

#endif /* DELAY_APP */

#endif /* INTPRINTER_HPP_ */
