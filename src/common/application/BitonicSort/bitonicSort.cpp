/*
 * bitonicSort.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: maselbas
 */



#include <bitonicSortParams.hpp>
#include <bitonicSource.hpp>
#include <bitonicPipe.hpp>
#include <bitonicOutput.hpp>

#ifdef BITONIC_SORT

class BitonicSortApp : public Application {
private:
public:
	ActorExecutor * getActorExecutor(Actor *actor){
		if(actor->function->compare("Source") == 0)
			return new Source(actor);
		else if(actor->function->compare("BitonicPipe") == 0)
			return new BitonicPipe(actor);
		else if(actor->function->compare("Output") == 0)
			return new Printer(actor);
		else
			return NULL;
	}

	void initApplication (ApplicationData *appData) {}
	void exitApplication (ApplicationData *appData) {}

};

Application * getApplication ()
{
	return new BitonicSortApp();
}

#endif /*  BITONIC_SORT */



