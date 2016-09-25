/*
 * printer.hpp
 *
 *  Created on: Jul 9, 2014
 *      Author: maselbas
 */

#ifndef PRINTER_HPP_
#define PRINTER_HPP_

#include <movingAverageParams.hpp>

#ifdef MOVINGAVERAGE_APP

class Printer : public ActorExecutor
{
private:

public:
	Printer (Actor *actor) : ActorExecutor(actor){}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		//pop 1
		int ** dataIn = (int **)getFifoData(0);

		cout << "printer: "<<*(dataIn[0]) << endl;

	}
};

#endif /* MOVINGAVERAGE_APP */

#endif /* PRINTER_HPP_ */
