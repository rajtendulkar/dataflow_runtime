/*
 * DelayApp.cpp
 *
 * 	Created on: Jun 16, 2014
 * 		Author: maselbas
 */

#include <delay.hpp>
#include <intPrinter.hpp>
#include <intSource.hpp>

#ifdef DELAY_APP

class DelayApp : public Application {
private:
public:
	ActorExecutor * getActorExecutor(Actor *actor){

		cout << "Resolving Actor : " << *(actor->function) << endl;

		if(actor->function->compare("IntSource") == 0)
			return new IntSource(actor);
		else if(actor->function->compare("Delay") == 0)
			return new Delay(actor);
		else if(actor->function->compare("IntPrinter") == 0)
			return new IntPrinter(actor);
		else
			return NULL;

	    cout << "Error : " << *(actor->function) << endl;
	}

	void initApplication (ApplicationData *appData){}
	void exitApplication (ApplicationData *appData){}

};

Application * getApplication(){
	return new DelayApp();
}

#endif /* DELAY_APP */
