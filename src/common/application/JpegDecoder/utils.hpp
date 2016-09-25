#ifndef UTILS_HPP
#define UTILS_HPP

/*
 * utils.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: rajtendulkar
 */


#include "jpeg.hpp"


#ifdef JPEG_DECODER

void aborted_stream()
{
	cout << "Aborting Stream" << endl;
	suicide();
}

/*----------------------------------------------------------*/

/*----------------------------------------------------------*/


/* Returns floor(N/D). */
int floor_div (int N, int D)
{
	int i = N / D;

	if (N < D * i)
		i--;
	return i;
}



/* Returns ceil(N/D). */
int ceil_div (int N, int D)
{
	int i = N / D;

	if (N > D * i)
		i++;
	return i;
}

/* For all components reset DC prediction value to 0. */
void reset_prediction (volatile JpgParams *params)
{
	int i;

	for (i = 0; i < 3; i++)
		params->comp[i].PRED = 0;
}

/* Transform JPEG number format into usual 2's-complement format. */
int reformat (unsigned long S, int good)
{
	int St;

	if (!good)
		return 0;
	St = 1 << (good - 1);	/* 2^(good-1) */
	if (S < (unsigned long) St)
		return (S + 1 + ( (-1) << good));
	else
		return S;
}

#endif /* JPEG_DECODER */


#endif /* UTILS_HPP */
