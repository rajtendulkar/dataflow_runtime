/*
 * peekApp.cpp
 *
 *  Created on: Jul 2, 2014
 *      Author: maselbas
 */

#include <peekParams.hpp>
#include <consumer.hpp>
#include <producer.hpp>

#ifdef PEEK_APP

class PeekApp : public Application
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


	void initApplication (ApplicationData *appData) {}
	void exitApplication (ApplicationData *appData) {}

};

Application * getApplication ()
{
	return new PeekApp();
}

#endif /* PEEK_APP */

