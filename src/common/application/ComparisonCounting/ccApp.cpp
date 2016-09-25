/*
 * ccApp.cpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */


#include <ccParams.hpp>
#include <ccSource.hpp>
#include <counter.hpp>
#include <countSplit.hpp>
#include <ccOutput.hpp>
#include <rearrangeIndices.hpp>

#ifdef COMPARISON_COUNTING

class CompCountingApp : public Application
{
private :
public:
	ActorExecutor * getActorExecutor(Actor *actor)
	{
		string jumpStr = "JumpSort";

		if(actor->function->compare("Source") == 0)
			return new IntSource(actor);
		else if(actor->function->compare("CountSplit") == 0)
			return new CountSplit(actor);
		else if(actor->function->compare("Counter") == 0)
			return new Counter(actor);
		else if(actor->function->compare("RearrangeIndices") == 0)
			return new RearrangeIndices(actor);
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
	return new CompCountingApp();
}

#endif /* INSERTION_SORT */
