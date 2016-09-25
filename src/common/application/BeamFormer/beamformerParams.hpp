/*
 * beamformerParams.hpp
 *
 *  Created on: Jan 6, 2014
 *      Author: rajtendulkar
 */

#ifndef BEAMFORMERPARAMS_HPP_
#define BEAMFORMERPARAMS_HPP_

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <parameters.hpp>
#include <shared_defs.hpp>

#define NUM_CHANNELS           		12
#define NUM_SAMPLES            		1024
#define NUMBEAMS              		4
#define NUM_COARSE_FILTER_TAPS   	64
#define NUM_FINE_FILTER_TAPS     	64
#define COARSE_DECIMATION_RATIO 	1
#define FINE_DECIMATION_RATIO   	2
#define NUM_SEGMENTS           		1
#define NUM_POST_DEC1           	NUM_SAMPLES / COARSE_DECIMATION_RATIO
#define NUM_POST_DEC2           	NUM_POST_DEC1 / FINE_DECIMATION_RATIO
#define MF_SIZE                		NUM_SEGMENTS * NUM_POST_DEC2
#define PULSE_SIZE             		NUM_POST_DEC2 / 2
#define PREDEC_PULSE_SIZE       	PULSE_SIZE * COARSE_DECIMATION_RATIO * FINE_DECIMATION_RATIO
#define TARGET_BEAM            		NUMBEAMS / 4
#define TARGET_SAMPLE          		NUM_SAMPLES / 4
#define TARGET_SAMPLE_POST_DEC   	TARGET_SAMPLE / COARSE_DECIMATION_RATIO / FINE_DECIMATION_RATIO
#define D_OVER_LAMBDA           	0.5
#define C_FAR_THRESHOLD         	0.95 * D_OVER_LAMBDA * NUM_CHANNELS * (0.5 * PULSE_SIZE)


#define BEAM_FORM_INSTANCES 4
#define DETECTOR_INSTANCES 4
#define MAGNITUDE_INSTANCES 4
#define INPUTGEN_INSTANCES 12


#endif /* BEAMFORMERPARAMS_HPP_ */
