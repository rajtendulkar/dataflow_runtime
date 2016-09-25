/*
 * radixSort.cpp
 *
 *  Created on: Jan 9, 2014
 *      Author: rajtendulkar
 */

#include <radixSortParams.hpp>
#include <sort.hpp>
#include <radixSource.hpp>
#include <radixOutput.hpp>

#ifdef RADIX_SORT

class RadixSortApp : public Application
{
private :
public:
	ActorExecutor * getActorExecutor(Actor *actor)
	{
		string radixStr = "Radix";

		if(actor->function->compare("Source") == 0)
			return new IntSource(actor);
		else if((actor->function->compare("Radix0") == 0) || 
				(actor->function->compare("Radix1") == 0) ||
				(actor->function->compare("Radix2") == 0) ||
				(actor->function->compare("Radix3") == 0) ||
				(actor->function->compare("Radix4") == 0) ||
				(actor->function->compare("Radix5") == 0) ||
				(actor->function->compare("Radix6") == 0) ||
				(actor->function->compare("Radix7") == 0) ||
				(actor->function->compare("Radix8") == 0) ||
				(actor->function->compare("Radix9") == 0) ||
				(actor->function->compare("Radix10") == 0))
			return new Sort(actor);
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
	return new RadixSortApp();
}

#endif /* RADIX_SORT */
