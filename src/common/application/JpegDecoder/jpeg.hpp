/*
 * jpeg.h
 *
 *  Created on: Jan 3, 2014
 *      Author: rajtendulkar
 */

#ifndef JPEG_HPP_
#define JPEG_HPP_

#include <parameters.hpp>

#ifdef JPEG_DECODER

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <assert.h>
#include "shared_defs.hpp"
#include "cluster_defs.hpp"
#include "fifo.hpp"
#include <actor.hpp>
#include <channel.hpp>
#include <fifoInfo.hpp>
#include <schedule.hpp>
#include <actorExecutor.hpp>

#define X_SIZE 32
#define Y_SIZE 24

#define DO_IMAGE_OUTPUT 1

// Number of Actor Instances
#define VLD_INSTANCES 1
#define IQIDCT_INSTANCES 12
#define COLOR_INSTANCES 12

// Port Definitions
#define VLD2IQIDCT_SRC_PORT 0
#define VLD2IQIDCT_DST_PORT 0
#define IQIDCT2COLOR_SRC_PORT 1
#define IQIDCT2COLOR_DST_PORT 0

// Port Rates
#define VLD_PORT_0_RATE			36
#define IQIDCT_PORT_0_RATE		3
#define IQIDCT_PORT_1_RATE		3
#define COLOR_PORT_0_RATE		3

#define INPUT_FILE_NAME "inputFiles/JpegDecoder/surfer.jpg"
#define OUTPUT_FILE_NAME "outputFiles/JpegDecoder/surfer.bmp"

/*----------------------------------*/
/* JPEG format parsing markers here */
/*----------------------------------*/

#define SOI_MK	0xFFD8		/* start of image	*/
#define APP_MK	0xFFE0		/* custom, up to FFEF */
#define COM_MK	0xFFFE		/* commment segment	*/
#define SOF_MK	0xFFC0		/* start of frame	*/
#define SOS_MK	0xFFDA		/* start of scan	*/
#define DHT_MK	0xFFC4		/* Huffman table	*/
#define DQT_MK	0xFFDB		/* Quant. table		*/
#define DRI_MK	0xFFDD		/* restart interval	*/
#define EOI_MK	0xFFD9		/* end of image		*/
#define MK_MSK	0xFFF0

#define RST_MK(x)	( (0xFFF8&(x)) == 0xFFD0 )
/* is x a restart interval ? */

/* Memory size of HTables; */
#define MAX_SIZE(hclass)        ((hclass)?162:14)

/*-------------------------------------------------------- */
/* all kinds of macros here				*/
/*-------------------------------------------------------- */

#define first_quad(c)   ((c) >> 4)        /* first 4 bits in file order */
#define second_quad(c)  ((c) & 15)

#define HUFF_ID(hclass, id)       (2 * (hclass) + (id))

#define DC_CLASS        0
#define AC_CLASS        1

#define suicide() { cout << "Committing Suicide" << endl; exit(1); }

/*-------------------------------------------------------*/
/* JPEG data types here					*/
/*-------------------------------------------------------*/

typedef union  		/* block of pixel-space values */
{
	unsigned char	block[8][8];
	unsigned char	linear[64];
} PBlock;

typedef union  		/* block of frequency-space values */
{
	int block[8][8];
	int linear[64];
} FBlock;


/* component descriptor structure */

typedef struct
{
	unsigned char	CID;	/* component ID */
	unsigned char	IDX;	/* index of first block in MCU */
	unsigned char	HS;	/* sampling factors */
	unsigned char	VS;
	unsigned char	HDIV;	/* sample width ratios */
	unsigned char	VDIV;
	char		QT;	/* QTable index, 2bits 	*/
	char		DC_HT;	/* DC table index, 1bit */
	char		AC_HT;	/* AC table index, 1bit */
	int		PRED;	/* DC predictor value */
} cd_t;

typedef struct
{
	unsigned int    x_size;
	unsigned int    y_size;    /* Video frame size     */
	unsigned int    rx_size;
	unsigned int	   ry_size;  /* down-rounded Video frame size (integer MCU) */
	unsigned int    MCU_sx;
	unsigned int	   MCU_sy;    /* MCU size in pixels   */
	unsigned int    mx_size;
	unsigned int	   my_size;  /* picture size in units of MCUs */
	unsigned int    n_comp;            /* number of components 1,3 */
	unsigned int    in_frame;          /* frame started ? current component ? */
	unsigned int    restart_interval;
	int    MCU_valid[10];     /* components of above MCU blocks */
	cd_t   comp[3];        	 /* descriptors for 3 components */
	unsigned int    QTvalid[4];		 /* Quantization Tables Valid */
	PBlock QTable[4];  		 /* quantization tables */
} JpgParams;

typedef struct
{
	unsigned int mcuRow;
	unsigned int mcuCol;
	unsigned int component;
	int vldBuffer[64];
}VLD2IDCT;

typedef struct
{
	unsigned int mcuRow;
	unsigned int mcuCol;
	unsigned int component;
	PBlock mcuBuff;
}IDCT2COLOR;

// extern JpgParams params;

typedef struct
{
	unsigned char   DC_Table0[MAX_SIZE (DC_CLASS)];
	unsigned char   DC_Table1[MAX_SIZE (DC_CLASS)];
	unsigned char   AC_Table0[MAX_SIZE (AC_CLASS)];
	unsigned char   AC_Table1[MAX_SIZE (AC_CLASS)];
	unsigned char   *HTable[4];
	/*=
	{
	&DC_Table0[0], &DC_Table1[0],
	&AC_Table0[0], &AC_Table1[0]
	};*/
	int MinCode[4][16];
	int MaxCode[4][16];
	int ValPtr[4][16];
} HuffTable;


typedef struct
{
	unsigned int *input_buffer;
	unsigned int vld_count;
	unsigned char bit_count;
	unsigned char window;
} VldParams;

typedef struct
{
	PBlock*             MCU_buff[10];      /* decoded DCT blocks buffer */
} JpgMcuBuffer;

extern unsigned int get_size (VldParams *vldParam);
extern void FOPEN_JPG (VldParams *vldParam, unsigned char *buffer);
extern unsigned int FGETC_JPG (VldParams *vldParam);
extern int FSEEK_JPG (VldParams *vldParam, int offset, int start);
extern void printVldParams(VldParams *vldParam);

extern void aborted_stream();
extern int floor_div (int N, int D);
extern int ceil_div (int N, int D);
extern void reset_prediction (volatile JpgParams *params);
extern int reformat (unsigned long S, int good);

extern unsigned long get_bits (VldParams *vldParam, int number);
extern void clear_bits (VldParams *vldParam);
extern unsigned char get_one_bit (volatile JpgParams *params, VldParams *vldParam);
extern void skip_segment (VldParams *vldParam);
extern unsigned int get_next_MK (VldParams *vldParam);
extern int load_quant_tables (volatile JpgParams *params, VldParams *vldParam);
extern int init_MCU (volatile JpgParams *params);
extern int load_huff_tables (VldParams *vldParam, HuffTable *table);
extern unsigned char get_symbol (volatile JpgParams *params, VldParams *vldParam, HuffTable *table, int select);
extern void unpack_block (volatile JpgParams *params, VldParams *vldParam, HuffTable *huffTable, int select, int *buffer);

extern void IDCT (const FBlock *input, PBlock *output);
extern void decodeJpgHeader (VldParams *vldParam, JpgParams *params, HuffTable *huffTable, unsigned char *srcBuffer);
extern void generateBitmapFile(int x_size, int y_size, unsigned char *FrameBuffer);

#endif /* JPEG_DECODER */
#endif /* JPEG_HPP_ */
