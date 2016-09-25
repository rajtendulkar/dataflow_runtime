/*
 * matrixParams.hpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rajtendulkar
 */

#ifndef MATRIXPARAMS_HPP_
#define MATRIXPARAMS_HPP_

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <actorExecutor.hpp>
#include <application.hpp>
#include <shared_defs.hpp>

#define X0 12
#define Y0 12

#define X1 9
#define Y1 12

#define BLOCKDIV 3

// Branch 0
// Source ->> Block split 0 ->> Duplicate0 ->> Joiner
// Branch 1
// Source ->> Block split 1 ->> Duplicate1 ->> Joiner
// Joiner ->> Block Multiply ->> Block Add ->> Block Combine ->> Print Output

// Source
#define SOURCE_INSTANCES 1
#define SOURCE_PORT0_RATE (X0*Y0)
#define SOURCE_PORT1_RATE (X1*Y1)

// Transpose same rate for input and output port.
#define TRANSPOSE_INSTANCES 1
#define TRANSPOSE_PORT_RATE (X1*Y1)

// Branch 0
#define BLOCK_SPLIT0_INSTANCES (BLOCKDIV)
#define BLOCK_SPLIT0_RATE ((X0 * Y0) / BLOCKDIV)

#define DUPLICATE0_INSTANCES (BLOCKDIV)
#define DUPLICATE0_INPUT_RATE ((X0 * Y0) / BLOCKDIV)
#define DUPLICATE0_OUTPUT_RATE (X0 * Y0)

// Branch 1
#define BLOCK_SPLIT1_INSTANCES (BLOCKDIV)
#define BLOCK_SPLIT1_RATE ((X1 * Y1) / BLOCKDIV)

#define DUPLICATE1_INSTANCES 1
#define DUPLICATE1_INPUT_RATE ((X1 * Y1) / BLOCKDIV)
#define DUPLICATE1_OUTPUT_RATE (X1 * Y1)

#define JOINER_INSTANCES (BLKDIV * BLKDIV * BLKDIV)
#define JOINER_INPUT_RATE0 (X0 * Y0 / (BLOCKDIV * BLOCKDIV))
#define JOINER_INPUT_RATE1 (X1 * Y1 / (BLOCKDIV * BLOCKDIV))

#define BLOCK_MULTIPLY_INSTANCES (BLKDIV * BLKDIV * BLKDIV)
#define BLOCK_MULTIPLY_INPUT_RATE ((X0*Y0)/(BLOCKDIV*BLOCKDIV) + (X1*Y1)/(BLOCKDIV*BLOCKDIV))
#define BLOCK_MULTIPLY_OUTPUT_RATE ((Y0*X1)/(BLOCKDIV*BLOCKDIV))

#define BLOCK_ADD_INSTANCES (1)
#define BLOCK_ADD_INPUT_RATE (X1 * Y0 / BLOCKDIV)
#define BLOCK_ADD_OUTPUT_RATE ((X1 * Y0) / (BLOCKDIV*BLOCKDIV))

#define BLOCK_SPLIT2_INSTANCES (1)
#define BLOCK_SPLIT2_RATE ((X1*Y0) / BLOCKDIV)

#define OUTPUT_INSTANCES (1)
#define OUTPUT_RATE (X1*Y0)

#endif /* MATRIXPARAMS_HPP_ */
