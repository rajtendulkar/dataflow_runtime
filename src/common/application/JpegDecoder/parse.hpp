#ifndef PARSE_HPP
#define PARSE_HPP

/*
 * parse.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: rajtendulkar
 */


#include "jpeg.hpp"

#ifdef JPEG_DECODER
/*---------------------------------------------------------------------*/


/* utility and counter to return the number of bits from file */
/* right aligned, masked, first bit towards MSB's		*/

//unsigned long get_bits (JpgParams *params, VldParams *vldParam, int number)
unsigned long get_bits (VldParams *vldParam, int number)
{
	int i, newbit;
	unsigned long result = 0;
	unsigned char aux, wwindow;

	if (!number)
		return 0;

	for (i = 0; i < number; i++)
	{
		if (vldParam->bit_count == 0)
		{
			wwindow = FGETC_JPG (vldParam);

			if (wwindow == 0xFF)
				switch (aux = FGETC_JPG (vldParam))  	/* skip stuffer 0 byte */
				{
					case 0xFF:
						aborted_stream ();
						break;

					case 0x00:
						// params->stuffers++;
						break;

					default:
						aborted_stream ();
						break;
				}

			vldParam->bit_count = 8;
		}
		else wwindow = vldParam->window;
		newbit = (wwindow >> 7) & 1;
		vldParam->window = wwindow << 1;
		vldParam->bit_count--;
		result = (result << 1) | newbit;
	}
	return result;
}


void clear_bits (VldParams *vldParam)
{
	vldParam->bit_count = 0;
}


unsigned char get_one_bit (volatile JpgParams *params, VldParams *vldParam)
{
	int newbit;
	unsigned char aux, wwindow;

	if (vldParam->bit_count == 0)
	{
		wwindow = FGETC_JPG (vldParam);

		if (wwindow == 0xFF)
			switch (aux = FGETC_JPG (vldParam))  	/* skip stuffer 0 byte */
			{
				case 0xFF:
					aborted_stream ();
					break;

				case 0x00:
					// params->stuffers++;
					break;

				default:
					aborted_stream ();
					break;
			}

		vldParam->bit_count = 8;
	}
	else
		wwindow = vldParam->window;

	newbit = (wwindow >> 7) & 1;
	vldParam->window = wwindow << 1;
	vldParam->bit_count--;
	return newbit;
}

/*----------------------------------------------------------*/


unsigned int get_size (VldParams *vldParam)
{
	unsigned char aux;

	aux = FGETC_JPG (vldParam);
	return (aux << 8) | FGETC_JPG (vldParam);	/* big endian */
}


/*----------------------------------------------------------*/


void skip_segment (VldParams *vldParam)	/* skip a segment we don't want */
{
	unsigned int size;
	int i;

	size = get_size (vldParam);
	if (size > 5)
	{
		for (i = 0; i < 4; i++)
			FGETC_JPG (vldParam);
		size -= 4;
	}
	FSEEK_JPG (vldParam, size - 2, SEEK_CUR);
}


/*----------------------------------------------------------------*/
/* find next marker of any type, returns it, positions just after */
/* EOF instead of marker if end of file met while searching ...	  */
/*----------------------------------------------------------------*/

//unsigned int get_next_MK (JpgParams *params, VldParams *vldParam)
unsigned int get_next_MK (VldParams *vldParam)
{
	unsigned int c;
	int ffmet = 0;
	// int locpassed = -1;

	// params->passed--;	/* as we fetch one anyway */

	while ((c = FGETC_JPG (vldParam)) != (unsigned int) EOF)
	{
		switch (c)
		{
			case 0xFF:
				ffmet = 1;
				break;
			case 0x00:
				ffmet = 0;
				break;
			default:
				if (ffmet)
					return (0xFF00 | c);
				ffmet = 0;
				break;
		}
		// locpassed++;
		// params->passed++;
	}

	return (unsigned int) EOF;
}


/*----------------------------------------------------------*/
/* loading and allocating of quantization table             */
/* table elements are in ZZ order (same as unpack output)   */
/*----------------------------------------------------------*/

int load_quant_tables (volatile JpgParams *params, VldParams *vldParam)
{
	char aux;
	unsigned int size, n, i, id, x;

	size = get_size (vldParam); /* this is the tables' size */
	n = (size - 2) / 65;

	for (i = 0; i < n; i++)
	{
		aux = FGETC_JPG (vldParam);
		if (first_quad (aux) > 0)
		{
			cout << "Exiting " << aux << endl;
			exit (1);
		}

		id = second_quad (aux);

		params->QTvalid[id] = 1;
		for (x = 0; x < 64; x++)
			params->QTable[id].linear[x] = FGETC_JPG (vldParam);
	}
	return 0;
}


/*----------------------------------------------------------*/
/* initialise MCU block descriptors	                    */
/*----------------------------------------------------------*/

int init_MCU (volatile JpgParams *params)
{
	unsigned int k, n, hmax = 0, vmax = 0;
	volatile int *MCU_valid = params->MCU_valid;
	volatile cd_t *comp = params->comp;

	for (unsigned int i = 0; i < 10; i++)
		MCU_valid[i] = -1;

	k = 0;

	for (unsigned int i = 0; i < params->n_comp; i++)
	{
		if (comp[i].HS > hmax)
			hmax = comp[i].HS;
		if (comp[i].VS > vmax)
			vmax = comp[i].VS;
		n = comp[i].HS * comp[i].VS;

		comp[i].IDX = k;
		for (unsigned int j = 0; j < n; j++)
		{
			MCU_valid[k] = i;
			k++;
			if (k == 10)
			{
				exit (1);
			}
		}
	}

	params->MCU_sx = 8 * hmax;
	params->MCU_sy = 8 * vmax;
	for (unsigned int i = 0; i < params->n_comp; i++)
	{
		comp[i].HDIV = (hmax / comp[i].HS > 1);	/* if 1 shift by 0 */
		comp[i].VDIV = (vmax / comp[i].VS > 1);	/* if 2 shift by one */
	}

	params->mx_size = ceil_div (params->x_size, params->MCU_sx);
	params->my_size = ceil_div (params->y_size, params->MCU_sy);
	params->rx_size = params->MCU_sx * floor_div (params->x_size, params->MCU_sx);
	params->ry_size = params->MCU_sy * floor_div (params->y_size, params->MCU_sy);

	return 0;
}

/*----------------------------------------------------------*/
/* Loading of Huffman table, with leaves drop ability	    */
/*----------------------------------------------------------*/

int load_huff_tables (VldParams *vldParam, HuffTable *table)
{
	char aux;
	int size, hclass, id, max;
	int LeavesN, LeavesT, i;
	int AuxCode;

	size = get_size (vldParam); /* this is the tables' size */

	size -= 2;

	while (size > 0)
	{

		aux = FGETC_JPG (vldParam);
		hclass = first_quad (aux);	/* AC or DC */
		id = second_quad (aux);	/* table no */
		if (id > 1)
		{
			exit (1);
		}

		id = HUFF_ID (hclass, id);
		size--;

		LeavesT = 0;
		AuxCode = 0;

		for (i = 0; i < 16; i++)
		{
			LeavesN = FGETC_JPG (vldParam);

			table->ValPtr[id][i] = LeavesT;
			table->MinCode[id][i] = AuxCode * 2;
			AuxCode = table->MinCode[id][i] + LeavesN;

			table->MaxCode[id][i] = (LeavesN) ? (AuxCode - 1) : (-1);
			LeavesT += LeavesN;
		}
		size -= 16;

		if (LeavesT > MAX_SIZE (hclass))
			max = MAX_SIZE (hclass);
		else
			max = LeavesT;

		for (i = 0; i < max; i++)
			table->HTable[id][i] = FGETC_JPG (vldParam);	/* load in raw order */

		for (i = max; i < LeavesT; i++) FGETC_JPG (vldParam);	/* skip if we don't load */
		size -= LeavesT;

	}	/* loop on tables */
	return 0;
}


/*-----------------------------------*/
/* extract a single symbol from file */
/* using specified huffman table ... */
/*-----------------------------------*/

unsigned char get_symbol (volatile JpgParams *params, VldParams *vldParam, HuffTable *table, int select)
{
	long code = 0;
	int length;
	int index;

	for (length = 0; length < 16; length++)
	{
		code = (2 * code) | get_one_bit (params, vldParam);

		if (code <= table->MaxCode[select][length])
			break;
	}

	index = table->ValPtr[select][length] + code - table->MinCode[select][length];

	if (index < MAX_SIZE (select / 2))
		return table->HTable[select][index];

	return 0;
}

#endif /* JPEG_DECODER */


#endif /* PARSE_HPP */
