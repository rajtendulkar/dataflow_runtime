/*
 * fifoApp.h
 *
 *  Created on: Dec 30, 2013
 *      Author: rajtendulkar
 */


#include <producer.hpp>
#include <consumer.hpp>
#include <application.hpp>

#ifdef FIFO_TEST_APP

class FifoApp : public Application
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
	return new FifoApp();
}

#endif

