/*
 * fft.cpp
 *
 *  Created on: Jan 11, 2014
 *      Author: rajtendulkar
 */


#include <fftParams.hpp>
#include <fftSource.hpp>
#include <fftReorderSimple.hpp>
#include <combineDft.hpp>
#include <fftOutput.hpp>

#ifdef FFT_APP

class FftApp : public Application
{
private :
public:
	ActorExecutor * getActorExecutor(Actor *actor)
	{

		if(actor->function->compare("Source") == 0)
			return new FFTTestSource(actor);
		else if((actor->function->compare("FftReorder0") == 0) || (actor->function->compare("FftReorder1") == 0)
				|| (actor->function->compare("FftReorder2") == 0) || (actor->function->compare("FftReorder3") == 0)
				|| (actor->function->compare("FftReorder4") == 0))
			return new FftReorder(actor);
		else if((actor->function->compare("CombineDft0") == 0) || (actor->function->compare("CombineDft1") == 0)
				|| (actor->function->compare("CombineDft2") == 0) || (actor->function->compare("CombineDft3") == 0)
				|| (actor->function->compare("CombineDft4") == 0) || (actor->function->compare("CombineDft5") == 0))
			return new CombineDFT(actor);
		else if(actor->function->compare("Output") == 0)
			return new FftOutput(actor);
		else
			return NULL;
	}

	void initApplication (ApplicationData *appData) {}
	void exitApplication (ApplicationData *appData) {}

};

Application * getApplication ()
{
	return new FftApp();
}

#endif /* FFT_APP */
