#ifndef GENERATEBITMAP_HPP
#define GENERATEBITMAP_HPP

/*
 * generateBitmap.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: rajtendulkar
 */

#include "jpeg.hpp"

#ifdef JPEG_DECODER

void generateBitmapFile(int x_size, int y_size, unsigned char *FrameBuffer)
{
	int i,j;
	FILE *outputFp = fopen(OUTPUT_FILE_NAME, "w+");
	if (outputFp == NULL)
	{
		cout << "Unable to Open OutputFile File : "  << OUTPUT_FILE_NAME << endl;
		return;
	}

	cout << "Generating Bitmap : " << x_size << " : " << y_size << endl;

	// Header and 3 bytes per pixel
	unsigned int ulBitmapSize = (y_size * x_size * 3) + 54;
	unsigned char temp;
	unsigned int tempInt;

	// BM
	temp = 66;
	fwrite (&temp, 1, sizeof(char),outputFp);
	temp = 77;
	fwrite (&temp, 1, sizeof(char),outputFp);
	// Size of the Image.
	fwrite (&ulBitmapSize, 1, sizeof(int),outputFp);

	// Reserved 4 bytes.
	tempInt = 0;
	fwrite (&tempInt, 1, sizeof(int),outputFp);

	// BMP Image Offset
	tempInt = 54;
	fwrite (&tempInt, 1, sizeof(int),outputFp);
	// Size of BitmapInfo Header 40 bytes.
	tempInt = 40;
	fwrite (&tempInt, 1, sizeof(int),outputFp);

	// Bitmap Width
	tempInt = x_size & 0x00FF;
	fwrite (&tempInt, 1, sizeof(int),outputFp);

	// Bitmap Height
	tempInt = (y_size & 0x00FF);
	fwrite (&tempInt, 1, sizeof(int),outputFp);

	// Rest can be found here - http://en.wikipedia.org/wiki/BMP_file_format
	temp = 1;
	fwrite (&temp, 1, sizeof(char),outputFp);
	temp = 0;
	fwrite (&temp, 1, sizeof(char),outputFp);
	temp = 24;
	fwrite (&temp, 1, sizeof(char),outputFp);
	temp = 0;
	fwrite (&temp, 1, sizeof(char),outputFp);

	tempInt = 0;
	for (i = 0; i < 6; i++)
		fwrite (&tempInt, 1, sizeof(int),outputFp);

	for (i = y_size - 1; i >= 0; i--)
	{
		/* in bitmaps the bottom line of the image is at the
		   beginning of the file */

		fwrite (&FrameBuffer[3 * (i * x_size)], 3 * x_size, sizeof(char),outputFp);

		temp = 0;
		for (j = 0; j < x_size % 4; j++)
			fwrite (&temp, 1, sizeof(char),outputFp);
	}

	fclose(outputFp);
}

#endif /* JPEG_DECODER */



#endif /* GENERATEBITMAP_HPP */
