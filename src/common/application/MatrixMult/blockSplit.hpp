/*
 * blockSplit.hpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef BLOCKSPLIT_HPP_
#define BLOCKSPLIT_HPP_

#include <matrixParams.hpp>

#ifdef MATRIX_MULT

class BlockSplit : public ActorExecutor
{
private:
	int x0, y0, blockDiv;

public:
	BlockSplit (Actor *actor) : ActorExecutor(actor)
	{
		this->x0 = 0;
		this->blockDiv = 0;
		this->y0 = 0;
	}
	~BlockSplit() {}

	void init (unsigned int instanceId, int x0, int y0, int blockDiv)
	{
		this->x0 = x0;
		this->y0 = y0;
		this->blockDiv = blockDiv;
	}

	void init (unsigned int instanceId)
	{
		if(actor->name->compare("BlockSplit0") == 0)
			 init (instanceId, X0, Y0, BLOCKDIV);
		else if(actor->name->compare("BlockSplit1") == 0)
			init (instanceId, Y1, X1, BLOCKDIV);
		else if(actor->name->compare("BlockSplit2") == 0)
			init (instanceId, X1 * Y0 / (BLOCKDIV * BLOCKDIV), Y0, Y0 / BLOCKDIV);
		else
		{
			throw std::runtime_error("This Block Split Actor is not supported. Check!!");
		}
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		float **inputData = (float**)getFifoData(0);
		float **outputData = (float**)getFifoData(1);

		for(int j=0;j<blockDiv;j++)
			for(int k=0;k<(y0/blockDiv);k++)
				for(int l=0;l<(x0/blockDiv);l++)
					*(outputData[j*((y0/blockDiv)*(x0/blockDiv)) + (x0/blockDiv)*k + l]) = *(inputData[j*(x0/blockDiv) + x0*k + l]);
	}
};

#endif /* MATRIX_MULT */
#endif /* BLOCKSPLIT_HPP_ */
