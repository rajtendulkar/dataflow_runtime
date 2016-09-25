/*
 * AutoCorApp.cpp
 *
 *  Created on: Jun 17, 2014
 *      Author: maselbas
 */

#include <autoCor.hpp>
#include <printer.hpp>
#include <source.hpp>


#ifdef AUTOCOR_APP

class AutoCorApp : public Application {
private:
public:
	ActorExecutor * getActorExecutor(Actor *actor){

		cout << "Resolving Actor : " << *(actor->function) << endl;

		if(actor->function->compare("Source") == 0)
			return new Source(actor);
		else if(actor->function->compare("AutoCor") == 0)
			return new AutoCor(actor);
		else if(actor->function->compare("Printer") == 0)
			return new Printer(actor);
		else
			return NULL;

	    cout << "Error : " << *(actor->function) << endl;
	}

	void initApplication (ApplicationData *appData){}
	void exitApplication (ApplicationData *appData){}

};

Application * getApplication(){
	return new AutoCorApp();
}

#endif /* AUTOCOR_APP */

