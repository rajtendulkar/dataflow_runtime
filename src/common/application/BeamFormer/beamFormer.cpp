/*
 * beamFormer.cpp
 *
 *  Created on: Jan 6, 2014
 *      Author: rajtendulkar
 */

#include <actorExecutor.hpp>
#include <schedule.hpp>
#include <applicationData.hpp>
#include <application.hpp>
#include <beamFilter.hpp>
#include <beamForm.hpp>
#include <beamformerduplicator.hpp>
#include <detector.hpp>
#include <inputGenerator.hpp>
#include <magnitude.hpp>

#ifdef BEAM_FOMER

class BeamFormerApp : public Application
{
private :
public:
	ActorExecutor * getActorExecutor(Actor *actor)
	{
		if(actor->function->compare("InputGenerate") == 0)
			return new InputGenerate(actor);
		else if(actor->function->compare("Detector") == 0)
			return new Detector(actor);
		else if ((actor->function->compare("BeamFirFilter0") == 0)
					|| (actor->function->compare("BeamFirFilter1") == 0)
					|| (actor->function->compare("BeamFirFilter2") == 0))
			return new BeamFirFilter(actor);
		else if(actor->function->compare("BeamForm") == 0)
			return new BeamForm(actor);
		else if(actor->function->compare("Magnitude") == 0)
			return new Magnitude(actor);
		else if(actor->function->compare("Duplicator") == 0)
			return new Duplicator(actor);
		else
			return NULL;
	}

	void initApplication (ApplicationData *appData) {}
	void exitApplication (ApplicationData *appData) {}

};

Application * getApplication ()
{
	return new BeamFormerApp();
}

#endif /* BEAM_FOMER */
