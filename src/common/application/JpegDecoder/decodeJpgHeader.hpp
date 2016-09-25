#ifndef DECODEJPGHEADER_HPP
#define DECODEJPGHEADER_HPP

/*
 * decodeHeader.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: rajtendulkar
 */


#include "jpeg.hpp"

#ifdef JPEG_DECODER

void decodeJpgHeader (VldParams *vldParam, JpgParams *params, HuffTable *huffTable, unsigned char *srcBuffer)
{
	unsigned int aux, mark;
	volatile cd_t *comp = params->comp;

	vldParam->bit_count = 0;
	vldParam->window = 0;

	huffTable->HTable[0] = & (huffTable->DC_Table0[0]);
	huffTable->HTable[1] = & (huffTable->DC_Table1[0]);
	huffTable->HTable[2] = & (huffTable->AC_Table0[0]);
	huffTable->HTable[3] = & (huffTable->AC_Table1[0]);

	params->restart_interval = 0;

	FOPEN_JPG (vldParam, srcBuffer);

	/* First find the SOI marker: */
	aux = get_next_MK (vldParam);
	if (aux != SOI_MK)
		aborted_stream();

	params->in_frame = 0;
	for (unsigned int i = 0; i < 4; i++)
		params->QTvalid[i] = 0;

	do
	{
		mark = get_next_MK (vldParam);
		switch (mark)
		{
		/* Start of Scan to do here */
		case SOS_MK:
			return;
			// taskVld (params, vldParam, huffTable, instanceId, fifoBuff, fifoCount);
			break;

		case SOF_MK:
			params->in_frame = 1;
			get_size (vldParam);   /* header size, don't care */

			/* load basic image parameters */
			FGETC_JPG (vldParam);   /* precision, 8bit, don't care */
			params->y_size = get_size (vldParam);
			params->x_size = get_size (vldParam);

			params->n_comp = FGETC_JPG (vldParam);  /* # of components */

			for (unsigned int i = 0; i < params->n_comp; i++)
			{
				/* component specifiers */
				comp[i].CID = FGETC_JPG (vldParam);
				aux = FGETC_JPG (vldParam);
				comp[i].HS = first_quad (aux);
				comp[i].VS = second_quad (aux);
				comp[i].QT = FGETC_JPG (vldParam);
			}

			if (init_MCU (params) == -1)
			{
				aborted_stream();
			}

#if 0
			// TODO: Hack to improve the speed.
			LOGMSG (1, "x : %d y : %d n : %d\n", params->x_size, params->y_size, params->n_comp);

			params->FrameBuffer = (unsigned char *) malloc ((size_t) params->x_size * params->y_size * params->n_comp * sizeof(unsigned char));
			if(params->FrameBuffer == NULL)
			{
				LOGERR("Error Allocating Memory\n");
				exit(1);
			}
#endif

			// memset(params->FrameBuffer, 0, params->x_size * params->y_size * params->n_comp);
			break;

		case DHT_MK:
			if (load_huff_tables (vldParam, huffTable) == -1)
			{
				aborted_stream();
			}
			break;

		case DQT_MK:
			if (load_quant_tables (params, vldParam) == -1)
			{
				aborted_stream();
			}
			break;

		case DRI_MK:
			get_size (vldParam);   /* skip size */
			params->restart_interval = get_size (vldParam);
			break;

		case EOI_MK:
			// Finished decoding.
			if (params->in_frame)
			{
				aborted_stream();
			}

			return;
			break;

		case COM_MK:
			skip_segment (vldParam);
			break;

		case EOF:
			aborted_stream();
			break;

		default:
			if ((mark & MK_MSK) == APP_MK)
			{
				skip_segment (vldParam);
				break;
			}
			if (RST_MK (mark))
			{
				reset_prediction (params);
				break;
			}
			aborted_stream();
			break;
		}
	}
	while (1);
}

#endif /* JPEG_DECODER */


#endif /* DECODEJPGHEADER_HPP */
