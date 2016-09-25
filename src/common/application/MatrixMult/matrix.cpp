/*
 * matrix.cpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */


#include <matrixSource.hpp>
#include <matrixParams.hpp>
#include <blockAdd.hpp>
#include <blockMultiply.hpp>
#include <blockSplit.hpp>
#include <Duplicate0.hpp>
#include <Duplicate1.hpp>
#include <Transpose.hpp>
#include <MatrixJoiner.hpp>
#include <matrixPrintOutput.hpp>


#ifdef MATRIX_MULT

class MatrixMultApp : public Application
{
private :
public:
	ActorExecutor * getActorExecutor(Actor *actor)
	{
		if(actor->function->compare("MatrixSource") == 0)
			return new MatrixSource(actor);
		else if(actor->function->compare("BlockAdd") == 0)
			return new BlockAdd(actor);
		else if(actor->function->compare("BlockMultiply") == 0)
			return new BlockMultiply(actor);
	        else if((actor->function->compare("BlockSplit0") == 0) || (actor->function->compare("BlockSplit1") == 0)
        	        || (actor->function->compare("BlockSplit2") == 0))
			return new BlockSplit(actor);
		else if(actor->function->compare("Duplicate0") == 0)
			return new Duplicate0(actor);
		else if(actor->function->compare("Duplicate1") == 0)
			return new Duplicate1(actor);
		else if(actor->function->compare("Transpose") == 0)
			return new Transpose(actor);
		else if(actor->function->compare("MatrixJoiner") == 0)
			return new MatrixJoiner(actor);
		else if(actor->function->compare("MatrixPrintOutput") == 0)
			return new MatrixPrintOutput(actor);
		else
			return NULL;
	}

	void initApplication (ApplicationData *appData) {}
	void exitApplication (ApplicationData *appData) {}

};

Application * getApplication ()
{
	return new MatrixMultApp();
}

#endif /* MATRIX_MULT */
