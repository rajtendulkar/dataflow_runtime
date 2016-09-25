/*
 * movingAverageApp.cpp
 *
 *  Created on: Jul 9, 2014
 *      Author: maselbas
 */

#include <movingAverageParams.hpp>
#include <source.hpp>
#include <averager.hpp>
#include <printer.hpp>

#ifdef MOVINGAVERAGE_APP

class MovingAveragerApp : public Application
{
private :
public:
	ActorExecutor * getActorExecutor(Actor *actor)
	{
		if(actor->function->compare("source") == 0)
			return new Source (actor);
		else if(actor->function->compare("averager") == 0)
			return new Averager(actor);
		else if(actor->function->compare("printer") == 0)
			return new Printer(actor);
		else
			return NULL;
	}

	void initApplication (ApplicationData *appData) {}
	void exitApplication (ApplicationData *appData) {}

};

Application * getApplication ()
{
	return new MovingAveragerApp();
}

#endif /* MOVINGAVERAGE_APP */
