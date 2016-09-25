/*
 * LowPassFilterApp.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: maselbas
 */

#include <LowPassFilterParams.hpp>
#include <FloatSource.hpp>
#include <FloatPrinter.hpp>
#include <LowPassFilter.hpp>

#ifdef LPF_APP

class LowPassFilterApp : public Application
{
private :
public:
	ActorExecutor * getActorExecutor(Actor *actor)
	{
		if(actor->function->compare("source") == 0)
			return new FloatSource(actor);
		else if(actor->function->compare("printer") == 0)
			return new FloatPrinter(actor);
		else if(actor->function->compare("lowPassFilter") == 0)
			return new LowPassFilter(actor);
		else
			return NULL;
	}


	void initApplication (ApplicationData *appData) {}
	void exitApplication (ApplicationData *appData) {}

};

Application * getApplication ()
{
	return new LowPassFilterApp();
}

#endif /* LPF_APP */

