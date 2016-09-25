/*
 * printer.hpp
 *
 *  Created on: Jun 17, 2014
 *      Author: maselbas
 */

#ifndef PRINTER_HPP_
#define PRINTER_HPP_

#include <autoCorParams.hpp>
#include <cluster_defs.hpp>

#ifdef AUTOCOR_APP

class Printer : public ActorExecutor {
private:
public:
	Printer(Actor *actor) : ActorExecutor(actor) {}

	void init(unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){

		float **data = (float**)getFifoData(0);

		cout << "Data  :" << *(data[0]) << endl;

	}

};

#endif /* AUTOCOR_APP */

#endif /* PRINTER_HPP_ */
