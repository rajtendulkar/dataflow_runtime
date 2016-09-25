/*
 * fifoApp.h
 *
 *  Created on: Dec 30, 2013
 *      Author: rajtendulkar
 */


#include <producerEmptyApp.hpp>
#include <consumerEmptyApp.hpp>
#include <emptyAppParams.hpp>

#ifdef EMPTY_APP

class EmptyApp : public Application
{
private :
public:
	ActorExecutor * getActorExecutor(Actor *actor)
	{
		if(actor->function->compare("producer") == 0)
			return new Producer(actor);
		else if(actor->function->compare("consumer") == 0)
			return new Consumer(actor);
		else
			return NULL;
	}


	void initApplication (ApplicationData *appData)
	{
	}

	void exitApplication (ApplicationData *appData) {}

};

Application * getApplication ()
{
	return new EmptyApp();
}

#endif /* EMPTY_APP */

