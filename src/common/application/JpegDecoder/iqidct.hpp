#ifndef IQIDCT_HPP
#define IQIDCT_HPP

/*
 * iqidct.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: rajtendulkar
 */

#include <jpeg.hpp>
#ifdef JPEG_DECODER

static const unsigned int G_ZZ[] =
{
		0,  1,  8, 16,  9,  2,  3, 10,
		17, 24, 32, 25, 18, 11,  4,  5,
		12, 19, 26, 33, 40, 48, 41, 34,
		27, 20, 13,  6,  7, 14, 21, 28,
		35, 42, 49, 56, 57, 50, 43, 36,
		29, 22, 15, 23, 30, 37, 44, 51,
		58, 59, 52, 45, 38, 31, 39, 46,
		53, 60, 61, 54, 47, 55, 62, 63
};
extern JpgParams jpgParams;

class IqIdct : public ActorExecutor
{
private:

	void izzIQ (volatile JpgParams *params, FBlock *T, int select, int *buffer)
	{
		int i;
		volatile cd_t *comp = params->comp;

		T->linear[0] = buffer[0];

		/* Dequantify and ZigZag-reorder: */
		for (i = 1; i < 64; i++)
			T->linear[G_ZZ[i]] = buffer[i] * params->QTable[(int)comp[select].QT].linear[i];
	}

	void taskIzzIq (volatile JpgParams *params, IDCT2COLOR **txBuffer, VLD2IDCT **rxBuffer)
	{
		FBlock FBuff;

		for (int curcomp = 0; params->MCU_valid[curcomp] != -1; curcomp++)
		{
			txBuffer[curcomp]->mcuRow = rxBuffer[curcomp]->mcuRow;
			txBuffer[curcomp]->mcuCol = rxBuffer[curcomp]->mcuCol;
			txBuffer[curcomp]->component = rxBuffer[curcomp]->component;

			izzIQ (params, &FBuff, params->MCU_valid[curcomp], rxBuffer[curcomp]->vldBuffer);
			IDCT (&FBuff, &(txBuffer[curcomp]->mcuBuff));
		}
	}

public:
	IqIdct (Actor *actor) : ActorExecutor(actor) {}

	void init(unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		// Max of this value is 10, as per JPEG Spec. But it also depends on the rate of the FIFO.
		VLD2IDCT **rxBuffer   = (VLD2IDCT **)   getFifoData(VLD2IQIDCT_DST_PORT);
		IDCT2COLOR **txBuffer = (IDCT2COLOR **) getFifoData(IQIDCT2COLOR_SRC_PORT);

		taskIzzIq (&jpgParams, txBuffer, rxBuffer);
	}
};

#endif /* JPEG_DECODER */

#endif /* IQIDCT_HPP */
