#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

/*
 * huffman.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: rajtendulkar
 */

#include <jpeg.hpp>

#ifdef JPEG_DECODER

#define HUFF_EOB		0x00
#define HUFF_ZRL		0xF0

/*-------------------------------------------------*/
/* here we unpack, predict, unquantify and reorder */
/* a complete 8*8 DCT block ...			   */
/*-------------------------------------------------*/

void unpack_block (volatile JpgParams *params, VldParams *vldParam, HuffTable *huffTable, int select, int *buffer)
{
	unsigned int i, run, cat;
	int value;
	unsigned char	symbol;
	volatile cd_t *comp = params->comp;
	volatile PBlock *qTable = params->QTable;

	/* Init the block with 0's: */
	memset (buffer, 0, 64 * sizeof (int));

	/* First get the DC coefficient: */
	symbol = get_symbol (params, vldParam, huffTable, HUFF_ID (DC_CLASS, comp[select].DC_HT));
	value = reformat (get_bits (vldParam, symbol), symbol);

	value += comp[select].PRED;
	comp[select].PRED = value;
	buffer[0] = value * qTable[ (int) comp[select].QT].linear[0];

	/* Now get all 63 AC values: */
	for (i = 1; i < 64; i++)
	{
		symbol = get_symbol (params, vldParam, huffTable, HUFF_ID (AC_CLASS, comp[select].AC_HT));
		if (symbol == HUFF_EOB) break;
		if (symbol == HUFF_ZRL)
		{
			i += 15;
			continue;
		}
		cat = symbol & 0x0F;
		run = (symbol >> 4) & 0x0F;
		i += run;
		buffer[i] = reformat (get_bits (vldParam, cat), cat);
	}
}

#endif /* JPEG_DECODER */

#endif /* HUFFMAN_HPP */
