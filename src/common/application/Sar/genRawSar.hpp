/*
 * genRawSar.hpp
 *
 *  Created on: Jun 23, 2014
 *      Author: maselbas
 */

#ifndef GENRAWSAR_HPP_
#define GENRAWSAR_HPP_

#include <sarParams.hpp>
#include <FFT.hpp>
#include <utils.hpp>

#ifdef SAR_APP

void genRawSar(complex ** output)
{
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// %%  Pre-determine the pixel size of the eventual image in the   %%
	// %%  X-dimm, to control placement of SAR returns relative to     %%
	// %%  pixel-based templates placement. (Code from formSARimage()) %%
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//
	float kxmin   = 1e25;
	float kxmax   = 0;
	float dkx     = PI / X0;
	int   is      = 8;
	int   nx      = 0;
	float   kx[n][m];

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// %%           Parameters of Targets                 %%
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//
	// % SAR reflectors within digital spotlight filter
	// % [targets in an equally spaced mesh, all with unity
	// % reflection coefficient.]

	/* letter image size */
	int N_pix     = 24;

	float npixx   = 0;
	float npixy   = 0;
	int   xni     = 0;
	int   yni     = 0;
	int   ntarget = 0;
	// NOTE: to statically resolve the value of ntarget requires aggressive
	// constant propagation of kx[][] which is 70K elements in size; so
	// hardcode ntarget = 48 for now
	float xn[48];
	float yn[48];
	float fn[48];


	/**********
	 * I N I T
	 **********/

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// %%  Pre-determine the pixel size of the eventual image in the   %%
	// %%  X-dimm, to control placement of SAR returns relative to     %%
	// %%  pixel-based templates placement. (Code from formSARimage()) %%
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	for (int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			float val = (4 * (k[i] * k[i])) - (ku[j] * ku[j]);

			if (val > 0) {
				kx[i][j] = sqrt(val);
			}
			else {
				kx[i][j] = 0;
			}

			if (kxmax < kx[i][j]) {
				kxmax = kx[i][j];
			}
			if (kxmin > kx[i][j]) {
				kxmin = kx[i][j];
			}
		}
	}

	nx = 2 * (int) ceil((0.5 * (kxmax - kxmin)) / dkx);
	nx = nx + 2 * is + 4;

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// %%           Parameters of Targets                 %%
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	npixx = (N_pix / (float) nx) * 2 * X0;
	npixy = (N_pix / (float) m ) * 2 * Y0;

	xni = (int) ((((2 * X0 - ceil(npixx / 2))
			- floor(npixx / 2))
			/ (2 * npixx))
			+ 1);

	yni = (int) ((((2 * Y0 - ceil(npixy / 2))
			- floor(npixy / 2))
			/ (2 * npixy))
			+ 1);

	/* number of targets */
	ntarget = xni * yni;

	for (int i = 0; i < xni; i++) {
		for (int j = 0; j < yni; j++) {
			xn[i * yni + j] = (floor(npixx / 2) + 2 * npixx * i) - X0;
			yn[i * yni + j] = (floor(npixy / 2) + 2 * npixy * j) - Y0;
			fn[i * yni + j] = 1;
		}
	}

	/**********
	 * W O R K
	 **********/

	float td[n][mc];
	complex S[n][mc];

	for (int h = 0; h < ntarget; h++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < mc; j++){
				td[i][j] = t[i] - 2 * sqrt(pow(Xc + xn[h], 2) + pow(yn[h] - uc[j], 2)) / c;

				if ((td[i][j] >= 0.0) && (td[i][j] <= Tp) && (abs(uc[j]) <= L) && (t[i] < Tf)) {
					float value  = PI2 * ((fc - f0) * td[i][j] + (f0 / Tp) * pow(td[i][j], 2));
					S[i][j].real += fn[h] * cos(value);
					S[i][j].imag += fn[h] * sin(value);
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		float cos_value = cos(PI2 * fc * t[i]);
		float sin_value = sin(PI2 * fc * t[i]);

		for (int j = 0; j < mc; j++) {


			complex out;

			out.real = S[i][j].real * cos_value + S[i][j].imag * sin_value;
			out.imag = S[i][j].imag * cos_value - S[i][j].real * sin_value;

			*(output[i*mc + j])= out;

		}
	}

}

void FastTimeFilter(complex** output){


	complex** pipe1 = new complex*[n];
	complex** pipe2 = new complex*[n];
	for(int i=0; i<n; i++){
		pipe1[i] = new complex;
		pipe2[i] = new complex;
	}


	/**********
	 * W O R K
	 **********/

	float td0[n];
	complex s0[n];
	complex ftf[n];
	for (int i = 0; i < n; i++) {
		td0[i] = t[i] - 2 * Xc / c;
		if ((td0[i] >= 0.0) && (td0[i] <= Tp)) {
			float value= PI2 * ((fc - f0) * td0[i] + (f0 / Tp) * pow(td0[i], 2));
			s0[i].real = cos(value);
			s0[i].imag = sin(value);
		}

		float value = PI2 * fc * t[i];
		float cos_value = cos(value);
		float sin_value = sin(value);

		ftf[i].real = s0[i].real * cos_value + s0[i].imag * sin_value;
		ftf[i].imag = s0[i].imag * cos_value - s0[i].real * sin_value;


		*(pipe1[i]) = ftf[i];

	}

	FTX1D(pipe1,pipe2,n);

	conjugate(pipe2,output);

	for(int i=0; i<n; i++){
		delete pipe1[i];
		delete pipe2[i];
	}
	delete[] pipe1;
	delete[] pipe2;

}



#endif /* SAR_APP_ */
#endif /* GENRAWSAR_HPP_ */
