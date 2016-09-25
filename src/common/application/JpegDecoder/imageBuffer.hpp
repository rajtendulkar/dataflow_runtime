#ifndef IMAGEBUFFER_HPP
#define IMAGEBUFFER_HPP

/*
 * imageBuffer.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: rajtendulkar
 */

#include "jpeg.hpp"

#ifdef JPEG_DECODER

void FOPEN_JPG (VldParams *vldParam, unsigned char *buffer)
{
	vldParam->input_buffer = (unsigned int*)buffer;
	vldParam->vld_count = 0;
}

unsigned int FGETC_JPG (VldParams *vldParam)
{
	unsigned int c = ((vldParam->input_buffer[vldParam->vld_count/4] >> (8 * (vldParam->vld_count % 4))) & 0x00ff);
	vldParam->vld_count++;
	return c;
}

int FSEEK_JPG (VldParams *vldParam, int offset, int start)
{
	vldParam->vld_count += offset;  /* Just to use start... */
	return 0;
}

void printVldParams(VldParams *vldParam)
{
	cout << "bitcount " << vldParam->bit_count << " vldcount " << vldParam->vld_count << " window " << vldParam->window << endl;
}

#endif /* JPEG_DECODER */

#endif /* IMAGEBUFFER_HPP */
