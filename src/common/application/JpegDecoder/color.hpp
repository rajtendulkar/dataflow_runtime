#ifndef COLOR_HPP
#define COLOR_HPP

/*
 * color.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: rajtendulkar
 */

#include "jpeg.hpp"

/* Ensure number is >=0 and <=255			   */
#define Saturate(n)	 ((n) > 0 ? ((n) < 255 ? (n) : 255) : 0)


#ifdef JPEG_DECODER

extern JpgParams jpgParams;
extern unsigned char FrameBuffer[X_SIZE * Y_SIZE * 3];

class Color : public ActorExecutor
{
private:
	JpgMcuBuffer mcu;
	unsigned char ColorBuffer[8 * 8 * 3];

	int process_colorConversion (volatile JpgParams *params, JpgMcuBuffer *mcu, unsigned int MCU_row,
						unsigned int MCU_column, unsigned char *FrameBuffer)
	{
		long offset;
		int  goodrows, goodcolumns;

		/* YCrCb to RGB color space transform here */
		if (params->n_comp > 1)
			color_conversion (params, mcu, ColorBuffer);
		else
			memmove (ColorBuffer, (mcu->MCU_buff[0]), 64);

		/* cut last row/column as needed */
		if ((params->y_size != params->ry_size) && (MCU_row == (params->my_size - 1)))
			goodrows = params->y_size - params->ry_size;
		else
			goodrows = params->MCU_sy;

		if ((params->x_size != params->rx_size) && (MCU_column == (params->mx_size - 1)))
			goodcolumns = params->x_size - params->rx_size;
		else
			goodcolumns = params->MCU_sx;

		offset = params->n_comp * ((MCU_row * params->MCU_sy * params->x_size) + (MCU_column * params->MCU_sx));

		for (int i = 0; i < goodrows; i++)
		{
			// LOGMSG (1, "x_size : %d MCU_sx : %d goodcol : %d goodrows : %d\n", params->x_size,params->MCU_sx,goodcolumns , goodrows);
			// cout << "I: " << i << " x_size : " << params->x_size << " MCU_sx : "<< params->MCU_sx << " goodcol : "
			//		<< goodcolumns << " goodrows : " << goodrows  << " ncomp : " << params->n_comp  << " offset : " << offset
			//		<< " MCU_row " << MCU_row << " MCU_col " << MCU_column << endl;
			memmove (FrameBuffer + offset + params->n_comp * i * params->x_size,
					ColorBuffer + params->n_comp * i * params->MCU_sx,
					params->n_comp * goodcolumns);
		}
		return 0;
	}

	void color_conversion (volatile JpgParams *params, JpgMcuBuffer *mcu, unsigned char* ColorBuffer)
	{
		unsigned char y, cb, cr;
		signed char rcb, rcr;
		long r, g, b;
		long offset;
		volatile cd_t *comp = params->comp;

		for (unsigned int i = 0; i < params->MCU_sy; i++)   /* pixel rows */
		{
			int ip_0 = i >> comp[0].VDIV;
			int ip_1 = i >> comp[1].VDIV;
			int ip_2 = i >> comp[2].VDIV;
			int inv_ndx_0 = comp[0].IDX + comp[0].HS * (ip_0 >> 3);
			int inv_ndx_1 = comp[1].IDX + comp[1].HS * (ip_1 >> 3);
			int inv_ndx_2 = comp[2].IDX + comp[2].HS * (ip_2 >> 3);
			int ip_0_lsbs = ip_0 & 7;
			int ip_1_lsbs = ip_1 & 7;
			int ip_2_lsbs = ip_2 & 7;
			int i_times_MCU_sx = i * params->MCU_sx;

			for (unsigned int j = 0; j < params->MCU_sx; j++)   /* pixel columns */
			{
				int jp_0 = j >> comp[0].HDIV;
				int jp_1 = j >> comp[1].HDIV;
				int jp_2 = j >> comp[2].HDIV;

				y  = mcu->MCU_buff[inv_ndx_0 + (jp_0 >> 3)]->block[ip_0_lsbs][jp_0 & 7];
				cb = mcu->MCU_buff[inv_ndx_1 + (jp_1 >> 3)]->block[ip_1_lsbs][jp_1 & 7];
				cr = mcu->MCU_buff[inv_ndx_2 + (jp_2 >> 3)]->block[ip_2_lsbs][jp_2 & 7];

				rcb = cb - 128;
				rcr = cr - 128;

				r = y + ((359 * rcr) >> 8);
				g = y - ((11 * rcb) >> 5) - ((183 * rcr) >> 8);
				b = y + ((227 * rcb) >> 7);

				offset = 3 * (i_times_MCU_sx + j);
				ColorBuffer[offset + 2] = Saturate (r);
				ColorBuffer[offset + 1] = Saturate (g);
				ColorBuffer[offset + 0] = Saturate (b);
				/* note that this is SunRaster color ordering */
			}
		}
	}

public:
	Color (Actor *actor) : ActorExecutor(actor) {}

	void init(unsigned int instanceId)
	{
		// Zero out the buffer.
		memset (&mcu, 0, sizeof(JpgMcuBuffer));
	}

	void execute (unsigned int instanceId, unsigned int iterationId)
	{
		IDCT2COLOR **rxBuff = (IDCT2COLOR **)getFifoData(0);

		for (int curcomp = 0; jpgParams.MCU_valid[curcomp] != -1; curcomp++)
			mcu.MCU_buff[curcomp] = &(rxBuff[curcomp]->mcuBuff);

		// Process MCU Block
		process_colorConversion (&jpgParams, &mcu, rxBuff[0]->mcuRow, rxBuff[0]->mcuCol, FrameBuffer);
	}
};

#endif /* JPEG_DECODER */
#endif /* COLOR_HPP */
