/*
 * lattice.cpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#include <latticeParams.hpp>
#include <latticeSource.hpp>
#include <latticeOutput.hpp>
#include <zeroStage.hpp>
#include <compStage.hpp>

#ifdef LATTICE_APP

class LatticeApp : public Application
{
private :
public:
	ActorExecutor * getActorExecutor(Actor *actor)
	{
		if(actor->function->compare("Source") == 0)
			return new IntSource(actor);
		else if(actor->function->compare("CompStage") == 0)
			return new CompStage(actor);
		else if(actor->function->compare("ZeroStage") == 0)
			return new ZeroStage(actor);
		else if(actor->function->compare("Output") == 0)
			return new IntPrinter(actor);
		else
			return NULL;
	}

	void initApplication (ApplicationData *appData) {}
	void exitApplication (ApplicationData *appData) {}

};

Application * getApplication ()
{
	return new LatticeApp();
}

#endif /* LATTICE_APP */
