/*
 * sarPrinter.hpp
 *
 *  Created on: Jun 23, 2014
 *      Author: maselbas
 */

#ifndef SARPRINTER_HPP_
#define SARPRINTER_HPP_

#ifdef SAR_APP

class Printer : public ActorExecutor
{
private:
public:
	Printer (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		//consume  nx * m = 266 * 382 = 101612
		float **data = (float **)getFifoData(0);
		for (int i=0; i< nx*m ; i++){
			cout << *(data[i]) << endl;
		}
	}
};

#endif /* SAR_APP */

#endif /* SARPRINTER_HPP_ */
