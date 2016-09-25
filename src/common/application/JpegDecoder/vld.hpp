#ifndef VLD_HPP
#define VLD_HPP

/*
 * vld.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: rajtendulkar
 */

#include "jpeg.hpp"

#ifdef JPEG_DECODER

extern JpgParams jpgParams;
extern VldParams vldParams;
extern HuffTable huffTable;

class Vld : public ActorExecutor
{
private:
	void taskVld (JpgParams *params, VldParams *vldParam, HuffTable *huffTable, int instanceId, int iterationId, Fifo *fifo)
	{
		unsigned int aux, fifoCount=0;
		unsigned int mcuCol = 0, mcuRow = 0;
		unsigned int n_restarts, leftover; /* RST check */
		volatile cd_t *comp = params->comp;
		VLD2IDCT **fifoBuff = (VLD2IDCT **)getFifoData(0);

		get_size (vldParam); /* don't care */
		aux = FGETC_JPG (vldParam);
		if (aux != (unsigned int) params->n_comp)
			aborted_stream ();

		for (unsigned int i = 0; i < params->n_comp; i++)
		{
			aux = FGETC_JPG (vldParam);
			if (aux != comp[i].CID)
				aborted_stream ();

			aux = FGETC_JPG (vldParam);
			comp[i].DC_HT = first_quad (aux);
			comp[i].AC_HT = second_quad (aux);
		}
		get_size (vldParam);
		FGETC_JPG (vldParam);   /* skip things */

		clear_bits (vldParam);
		reset_prediction (params);

		/* main MCU processing loop here */
		if (params->restart_interval)
		{
			n_restarts = ceil_div (params->mx_size * params->my_size, params->restart_interval) - 1;
			leftover = params->mx_size * params->my_size - n_restarts * params->restart_interval;
			/* final interval may be incomplete */

			for (unsigned int i = 0; i < n_restarts; i++)
			{
				for (unsigned int j = 0; j < params->restart_interval; j++)
				{
					int curcomp;

					if (mcuCol == params->mx_size)
					{
						mcuCol = 0;
						mcuRow++;
						if (mcuRow == params->my_size)
						{
							params->in_frame = 0;
							continue;
						}
					}

					for (curcomp = 0; params->MCU_valid[curcomp] != -1; curcomp++)
					{
						VLD2IDCT *vldBuff = fifoBuff[fifoCount];
						fifoCount++;
						vldBuff->mcuCol = mcuCol;
						vldBuff->mcuRow = mcuRow;
						vldBuff->component =  curcomp;
						unpack_block (params, vldParam, huffTable, params->MCU_valid[curcomp], vldBuff->vldBuffer);
					}
					mcuCol++;
				}

				/* proc till all EOB met */
				aux = get_next_MK (vldParam);
				if (!RST_MK (aux))
					aborted_stream ();

				reset_prediction (params);
				clear_bits (vldParam);
			}       /* intra-interval loop */
		}
		else
			leftover = params->mx_size * params->my_size;

		/* process till end of row without restarts */
		for (unsigned int i = 0; i < leftover; i++)
		{
			int curcomp;

			if (mcuCol == params->mx_size)
			{
				mcuCol = 0;
				mcuRow++;

				if (mcuRow == params->my_size)
				{
					params->in_frame = 0;
					continue;
				}
			}

			for (curcomp = 0; params->MCU_valid[curcomp] != -1; curcomp++)
			{
				VLD2IDCT *vldBuff = fifoBuff[fifoCount];
				fifoCount++;
				vldBuff->mcuCol = mcuCol;
				vldBuff->mcuRow = mcuRow;
				vldBuff->component =  curcomp;
				unpack_block (params, vldParam, huffTable, params->MCU_valid[curcomp], vldBuff->vldBuffer);
			}
			mcuCol++;
		}

		params->in_frame = 0;
	}

public:
	Vld (Actor *actor) : ActorExecutor(actor) {}

	void init(unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		Fifo *fifo = getFifo(VLD2IQIDCT_SRC_PORT);
		int count = vldParams.vld_count;
		taskVld ((JpgParams *)&jpgParams, (VldParams *)&vldParams, (HuffTable *)&huffTable, instanceId, iterationId, fifo);
		vldParams.vld_count = count; // Just reset the counter in case if we execute multiple iterations in decoding same image.
	}
};

#endif /* JPEG_DECODER */

#endif /* VLD_HPP */
