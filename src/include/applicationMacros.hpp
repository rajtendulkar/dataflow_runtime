/*
 * applicationMacros.hpp
 *
 *  Created on: Jan 24, 2014
 *      Author: rajtendulkar
 */

#ifndef APPLICATIONMACROS_HPP_
#define APPLICATIONMACROS_HPP_

// When you execute the makefile, you should always execute the command like this -
// make all APPLICATION=FifoTestApp
// it should be the name of the directory.

// Just add whatever macros you want. just remember that you will get a define
// here from the make file from command line equal to name of your application directory
// in upper case.

// numbers don't matter, just give them a unique number and not zero.
// Also the macro should be same as the name of application directory in upper case.
#define FIFOTESTAPP 					1
#define JPEGDECODER 					2
#define BEAMFORMER 						3
#define DCT 							4
#define MATRIXMULT 						5
#define RADIXSORT 						6
#define MERGESORT 						7
#define INSERTIONSORT 					8
#define COMPARISONCOUNTING 				9
#define LATTICE 						10
#define TDE 							11
#define FFT 							12
#define BATCHERSORT 					13
#define EMPTYAPP 						14
#define DELAY							15
#define AUTOCOR							16
#define BITONICSORT						17
#define SAR								18
#define FILTERBANKAPP					19
#define PEEKTESTAPP						20
#define MOVINGAVERAGE					21
#define LOWPASSFILTER					22

// If you don't want to pass from the make file just make a definition like this.
// #define APPLICATION FIFOTESTAPP

#if(APPLICATION == FIFOTESTAPP)
#define FIFO_TEST_APP
#endif

#if (APPLICATION == JPEGDECODER)
#define JPEG_DECODER
#endif

#if (APPLICATION == BEAMFORMER)
#define BEAM_FOMER
#endif

#if (APPLICATION == DCT)
#define DCT_APP
#endif

#if (APPLICATION == MATRIXMULT)
#define MATRIX_MULT
#endif

#if (APPLICATION == RADIXSORT)
#define RADIX_SORT
#endif

#if (APPLICATION == MERGESORT)
#define MERGE_SORT
#endif

#if (APPLICATION == INSERTIONSORT)
#define INSERTION_SORT
#endif

#if (APPLICATION == COMPARISONCOUNTING)
#define COMPARISON_COUNTING
#endif

#if (APPLICATION == LATTICE)
#define LATTICE_APP
#endif

#if (APPLICATION == TDE)
#define TDE_APP
#endif

#if (APPLICATION == FFT)
#define FFT_APP
#endif

#if(APPLICATION == BATCHERSORT)
#define BATCHER_SORT
#endif

#if (APPLICATION == EMPTYAPP)
#define EMPTY_APP
#endif

#if (APPLICATION == DELAY)
#define DELAY_APP
#endif

#if (APPLICATION == AUTOCOR)
#define AUTOCOR_APP
#endif

#if (APPLICATION == BITONICSORT)
#define BITONIC_SORT
#endif

#if (APPLICATION == SAR)
#define SAR_APP
#endif

#if (APPLICATION == FILTERBANKAPP)
#define FILTERBANK_APP
#endif

#if (APPLICATION == PEEKTESTAPP)
#define PEEK_APP
#endif

#if (APPLICATION == MOVINGAVERAGE)
#define MOVINGAVERAGE_APP
#endif

#if (APPLICATION == LOWPASSFILTER)
#define LPF_APP
#endif

#endif /* APPLICATIONMACROS_HPP_ */
