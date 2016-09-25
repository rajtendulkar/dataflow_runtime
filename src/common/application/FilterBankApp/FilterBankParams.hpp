/*
 * FilterBankParams.hpp
 *
 *  Created on: Jun 30, 2014
 *      Author: maselbas
 */

#ifndef FILTERBANKPARAMS_HPP_
#define FILTERBANKPARAMS_HPP_

#include <iostream>
#include <actorExecutor.hpp>
#include <application.hpp>
#include <shared_defs.hpp>
#include <parameters.hpp>
#include <fifo.hpp>


#ifdef FILTERBANK_APP

/************
 * C O N S T
 ************/

int N_samp = 8;
int N_ch = 8;
int N_col = 32;

float H[8][32];
float F[8][32];



#endif /* FILTERBANK_APP */
#endif /* FILTERBANKPARAMS_HPP_ */
