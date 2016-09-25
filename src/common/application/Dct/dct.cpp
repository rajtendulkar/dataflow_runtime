/*
 * dct.cpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#include <dctParams.hpp>
#include <dct2DCoarse.hpp>
#include <dct2DFine.hpp>
#include <idct2DCoarse.hpp>
#include <idct2DFastCoarse.hpp>
#include <idct2DFastFine.hpp>
#include <idct2DFine.hpp>
#include <dctJoiner.hpp>
#include <dctInputGenerate.hpp>
#include <dctPrintOutput.hpp>

#ifdef DCT_APP

class DctApp : public Application
{
private :
public:
	ActorExecutor * getActorExecutor(Actor *actor)
	{
		// All IDCT Actors
		if(actor->function->compare("Idct1DColFast") == 0)
			return new Idct1DColFast(actor);
		else if(actor->function->compare("Idct1DRowFast") == 0)
			return new Idct1DRowFast(actor);
		else if(actor->function->compare("Idct1DColFastFine") == 0)
			return new Idct1DColFastFine(actor);
		else if(actor->function->compare("Idct2DCoarse") == 0)
			return new Idct2DCoarse(actor);
		else if((actor->function->compare("Idct1DFine0") == 0) || (actor->function->compare("Idct1DFine1") == 0))
			return new Idct1DFine(actor);

		// All DCT Actors
		else if ((actor->function->compare("DCT1DFine0") == 0) || (actor->function->compare("DCT1DFine1") == 0))
			return new DCT1DFine(actor);
		else if(actor->function->compare("Dct2DCoarse") == 0)
			return new Dct2DCoarse(actor);

		// Miscellaneous Actors
		else if((actor->function->compare("DctJoiner0") == 0) || (actor->function->compare("DctJoiner1") == 0) 
					|| (actor->function->compare("DctJoiner2") == 0) ||  (actor->function->compare("DctJoiner3") == 0))
			return new DctJoiner(actor);
		else if(actor->function->compare("DctInputGenerate") == 0)
			return new DctInputGenerate(actor);
		else if(actor->function->compare("DctPrintOutput") == 0)
			return new DctPrintOutput(actor);
		else
			return NULL;
	}

	void initApplication (ApplicationData *appData) {}
	void exitApplication (ApplicationData *appData) {}

};

Application * getApplication ()
{
	return new DctApp();
}
#endif /* DCT_APP */
