/*
 * mergeSort.cpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#include <mergeSortParams.hpp>
#include <merger.hpp>
#include <mergeOutput.hpp>
#include <mergeOutput.hpp>
#include <mergeSource.hpp>
#include <splitter.hpp>
#include <joiner.hpp>

#ifdef MERGE_SORT

class MergeSortApp : public Application
{
private :
public:
	ActorExecutor * getActorExecutor(Actor *actor)
	{
		if(actor->function->compare("Source") == 0)
			return new IntSource(actor);
		else if((actor->function->compare("Merger0") == 0) || (actor->function->compare("Merger1") == 0)
				|| (actor->function->compare("Merger2") == 0) || (actor->function->compare("Merger3") == 0))
			return new Merger(actor);
		else if((actor->function->compare("Split0") == 0) || (actor->function->compare("Split1") == 0)
				|| (actor->function->compare("Split2") == 0))
			return new InputSplitter(actor);
		else if((actor->function->compare("Join0") == 0) || (actor->function->compare("Join1") == 0)
				|| (actor->function->compare("Join2") == 0))
			return new OutputJoiner(actor);
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
	return new MergeSortApp();
}

#endif /* MERGE_SORT */
