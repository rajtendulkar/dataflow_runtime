/*
 * tdeParams.hpp
 *
 *  Created on: Jan 9, 2014
 *      Author: rajtendulkar
 */

#ifndef TDEPARAMS_HPP_
#define TDEPARAMS_HPP_

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <actorExecutor.hpp>
#include <application.hpp>
#include <shared_defs.hpp>

#define CH  6 // N_CH in C Code.
    /* The number of range (distance from antenna) gates. */
#define N 36 // number of input samples  (N_RG in C Code)
    /* Pulse repetition intervals per data cube */
#define M  15 // number of pri's in a  (N_PRI in C Code)
#define B 64 // smallest power of 2 above N
                // Data is [N_CH][N_RG][N_PRI][2]
#define mult  0.00390625 // multiplier
#define DataParallelism  1 // any number 0 < DataParallelism <= N
#define FFTDataParallelism  2

#define SOURCE_ARRAY_SIZE 36*2*CH*M


#endif /* TDEPARAMS_HPP_ */
