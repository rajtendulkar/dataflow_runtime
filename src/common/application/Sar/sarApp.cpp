/*
 * sarApp.cpp
 *
 *  Created on: Jun 23, 2014
 *      Author: maselbas
 */

#include <application.hpp>

#include <sarCompression.hpp>
#include <sarDecompression.hpp>
#include <sarReconstruction.hpp>

#include <sarFastFilter.hpp>
#include <sarGenRawSar.hpp>
#include <sarRRjoin.hpp>

#include <sarZeroPadding.hpp>

#include <sarFTX2D.hpp>
#include <sar-iFTX2D.hpp>
#include <sarFTY2D.hpp>
#include <sar-iFTY2D.hpp>

#include <sarPrinter.hpp>

#include <sarParams.hpp>


#ifdef SAR_APP

class SarApp : public Application
{
private :
public:
	ActorExecutor * getActorExecutor(Actor *actor)
	{
		if(actor->function->compare("fastFilter") == 0)
			return new FastFilter(actor);
		else if(actor->function->compare("genRawSar") == 0)
			return new GenRawSar(actor);
		else if(actor->function->compare("FTX2D-gen2join") == 0)
			return new Cftx2d(actor);
		else if(actor->function->compare("joinFilter") == 0)
			return new RRjoin(actor);
		else if(actor->function->compare("compression") == 0)
			return new Compression(actor);
		else if(actor->function->compare("FTY2D-comp2padd") == 0)
			return new Cfty2d(actor,n,mc);
		else if(actor->function->compare("zeroPadding") == 0)
			return new ZeroPadding(actor);
		else if(actor->function->compare("iFTY2D-padd2decomp") == 0)
			return new Cifty2d(actor,n,m);
		else if(actor->function->compare("decompression") == 0)
			return new Decompression(actor);
		else if(actor->function->compare("FTY2D-decomp2reconst") == 0)
			return new Cfty2d(actor,n,m);
		else if(actor->function->compare("reconstruction") == 0)
			return new Reconstruction(actor);
		else if(actor->function->compare("printer") == 0)
			return new Printer(actor);
		else
			return NULL;
	}


	void initApplication (ApplicationData *appData) {}
	void exitApplication (ApplicationData *appData) {}

};

Application * getApplication ()
{
	return new SarApp();
}

#endif /* SAR_APP */


