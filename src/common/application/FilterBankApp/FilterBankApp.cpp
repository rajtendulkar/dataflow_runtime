/*
 * FilterBankApp.cpp
 *
 *  Created on: Jun 30, 2014
 *      Author: maselbas
 */


#include <FilterBankParams.hpp>
#include <source.hpp>
#include <splitBranche.hpp>
#include <firFilter.hpp>
#include <samp.hpp>
#include <joinBranche.hpp>
#include <combine.hpp>
#include <sink.hpp>

#ifdef FILTERBANK_APP

class FilterBank : public Application {
private:
public:
	ActorExecutor * getActorExecutor(Actor *actor){

		if(actor->function->compare("source") == 0)
			return new Source(actor);
		else if(actor->function->compare("splitBranche") == 0)
			return new SplitBranche(actor);
		else if(actor->function->compare("firFilter1-1") == 0)
			return new FirFilter(actor,H[0]);
		else if(actor->function->compare("firFilter2-1") == 0)
			return new FirFilter(actor,F[0]);

		else if(actor->function->compare("firFilter1-2") == 0)
			return new FirFilter(actor,H[1]);
		else if(actor->function->compare("firFilter2-2") == 0)
			return new FirFilter(actor,F[1]);

		else if(actor->function->compare("firFilter1-3") == 0)
			return new FirFilter(actor,H[2]);
		else if(actor->function->compare("firFilter2-3") == 0)
			return new FirFilter(actor,F[2]);

		else if(actor->function->compare("firFilter1-4") == 0)
			return new FirFilter(actor,H[3]);
		else if(actor->function->compare("firFilter2-4") == 0)
			return new FirFilter(actor,F[3]);

		else if(actor->function->compare("firFilter1-5") == 0)
			return new FirFilter(actor,H[4]);
		else if(actor->function->compare("firFilter2-5") == 0)
			return new FirFilter(actor,F[4]);

		else if(actor->function->compare("firFilter1-6") == 0)
			return new FirFilter(actor,H[5]);
		else if(actor->function->compare("firFilter2-6") == 0)
			return new FirFilter(actor,F[5]);

		else if(actor->function->compare("firFilter1-7") == 0)
			return new FirFilter(actor,H[6]);
		else if(actor->function->compare("firFilter2-7") == 0)
			return new FirFilter(actor,F[6]);

		else if(actor->function->compare("firFilter1-8") == 0)
			return new FirFilter(actor,H[7]);
		else if(actor->function->compare("firFilter2-8") == 0)
			return new FirFilter(actor,F[7]);

		else if(actor->function->compare("samp") == 0)
			return new Samp(actor);
		else if(actor->function->compare("joinBranche") == 0)
			return new JoinBranche(actor);
		else if(actor->function->compare("combine") == 0)
			return new Combine(actor);
		else if(actor->function->compare("sink") == 0)
			return new Sink(actor);
		else
			return NULL;

	    cout << "Error : " << *(actor->function) << endl;
		return NULL;
	}

	void initApplication (ApplicationData *appData){
		for (int i = 0; i < N_col; i++)
			for (int j = 0; j < N_ch; j++)
			{
				H[j][i] = i * N_col + j * N_ch + j + i + j + 1;
				F[j][i] = i * j + j * j + j + i;
			}
	}
	void exitApplication (ApplicationData *appData){}

};

Application * getApplication(){
	return new FilterBank();
}

#endif /* FILTERBANK_APP */



