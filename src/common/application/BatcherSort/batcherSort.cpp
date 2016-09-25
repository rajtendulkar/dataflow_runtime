/*
 * batcherSort.cpp
 *
 *  Created on: Jan 11, 2014
 *      Author: rajtendulkar
 */

#include <batcherSortParams.hpp>
#include <batcherSource.hpp>
#include <batcherPipe.hpp>
#include <batcherOutput.hpp>

#ifdef BATCHER_SORT
class BatcherSortApp : public Application
{
private :
public:
	ActorExecutor * getActorExecutor(Actor *actor)
	{
		if(actor->function->compare("Source") == 0)
			return new IntSource(actor);
		else if(actor->function->compare("BatcherPipe") == 0)
			return new BatcherPipe(actor);
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
	return new BatcherSortApp();
}

#endif /* BATCHER_SORT */
