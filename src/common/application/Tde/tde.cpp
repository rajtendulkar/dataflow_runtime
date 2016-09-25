/*
 * tde.cpp
 *
 *  Created on: Jan 10, 2014
 *      Author: rajtendulkar
 */

#include <tdeParams.hpp>
#include <tdeSource.hpp>
#include <contract.hpp>
#include <expand.hpp>
#include <combineDftTde.hpp>
#include <combineIdftFinal.hpp>
#include <combineIdft.hpp>
#include <fftReorder.hpp>
#include <tdeOutput.hpp>
#include <transpose.hpp>
#include <multiplyByFloat.hpp>


#ifdef TDE_APP

class TdeApp : public Application
{
private :
public:
	ActorExecutor * getActorExecutor(Actor *actor)
	{
		if(actor->function->compare("Source") == 0)
			return new TdeSource(actor);
		else if(actor->function->compare("Output") == 0)
			return new FloatPrinter(actor);
		else if(actor->function->compare("Transpose") == 0)
			return new Transpose(actor);
		else if(actor->function->compare("Expand") == 0)
			return new Expand(actor);
		else if(actor->function->compare("Contract") == 0)
			return new Contract(actor);
		else if(actor->function->compare("MultiplyByFloat") == 0)
			return new MultiplyByFloat(actor);
		else if(actor->function->compare("CombineIdftFinal") == 0)
			return new CombineIdftFinal(actor);
		else if(actor->function->compare("CombineDft") == 0)
			return new CombineDft(actor);
		else if(actor->function->compare("CombineIdft") == 0)
			return new CombineIdft(actor);
		else if(actor->function->compare("FftReorder") == 0)
			return new FftReorder(actor);
		else
		{
			cout << "Actor not found : " << actor->name << endl;
			return NULL;
		}
	}

	void initApplication (ApplicationData *appData) {}
	void exitApplication (ApplicationData *appData) {}

};

Application * getApplication ()
{
	return new TdeApp();
}

#endif /* TDE_APP */
