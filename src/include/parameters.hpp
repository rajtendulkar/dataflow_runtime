/*
 * parameters.h
 *
 *  Created on: Dec 28, 2013
 *      Author: rajtendulkar
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

// This file contains the parameters which can be configured for execution.

// Enable hardware tracing of points.
// #define ENABLE_KALRAY_TRACE


#define DEFAULT_INPUT_XML_FILE ""

#define DEFAULT_PROFILE_OUTPUT_FILE "defaultProfile.xml"

// How many time a schedule is executed on a processor of a cluster.
#define NUM_ITERATIONS 100

// Enable a global barrier between all the clusters for each iteration.
// #define INTER_ITERATION_BARRIER

// Enable flushing fifo between each iteration
// may not be working on HOST
#ifdef INTER_ITERATION_BARRIER
// #define INTER_ITERATION_FIFO_FLUSH
#endif

// There are 4 data points
#define PROFILE_DATA_SIZE_IN_BYTES (NUM_ITERATIONS * 4 * sizeof(uint64_t))
#define PROFILE_DATA_SIZE 		   (NUM_ITERATIONS * 4)

#include <applicationMacros.hpp>

#endif /* PARAMETERS_H_ */
