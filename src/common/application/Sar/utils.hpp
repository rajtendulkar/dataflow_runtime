/*
 * Utils.hpp
 *
 *  Created on: Jun 24, 2014
 *      Author: maselbas
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <sarParams.hpp>

/* complex -> complex */
void conjugate(complex **input, complex **output){
	complex out;
	for (int i = 0; i < n; i++) {
		out.real =  (input[i])->real;
		out.imag = -(input[i])->imag;
		*(output[i])=out;
	}
}

/* complex -> float */
void complexAbsoluate(complex **input, float **output,int n){
	for (int i=0; i<n ; i++){
		complex in = *(input[i]);
		float  out = sqrt(pow(in.real, 2) +
				pow(in.imag, 2));
		*(output[i])=out;
	}
}

/* float -> float */
void floatTranspose(float **input, float **output, int rows, int cols){
	for (int j = 0; j < cols; j++){
		for (int i = 0; i < rows; i++){
			//push(peek(i * cols + j));
			*(output[j * rows + i])=*(input[i * cols +j]);
		}
	}
}

/* complex -> complex */
void matchedFiltering(complex **input, complex **output){
		// NOTE: <kx> is redefined because of a lack of proper support
	    // for global arrays; the array itself is too big to be fully
	    // unrolled since it leads to 1.4M lines of code and chokes gcc
	    float   kx[n][m];
	    complex fs0[n][m];

	    /* init */
	    for (int i = 0; i < n; i++) {
	    	for(int j = 0; j < m; j++) {
	    		float val = (4 * (k[i] * k[i])) - (ku[j] * ku[j]);

	    		if (val > 0) {
	    			kx[i][j] = sqrt(val);
	    		}
	    		else {
	    			kx[i][j] = 0;
	    		}
	    	}
	    }


	    for (int i = 0; i < n; i++) {
	    	for (int j = 0; j < m; j++) {
	    		if (kx[i][j] > 0) {
	    			float value = kx[i][j] * Xc + ku[j] + 0.25 * PI - 2 * k[i] * Xc;
	    			fs0[i][j].real = cos(value);
	    			fs0[i][j].imag = sin(value);
	    		}
	    	}
	    }

	    /* work */
	    for (int i = 0; i < n; i++) {
	    	for (int j = 0; j < m; j++) {
	    		complex fs = *(input[i * m + j]);
	    		complex out;

	    		out.real = fs.real * fs0[i][j].real - fs.imag * fs0[i][j].imag;
	    		out.imag = fs.real * fs0[i][j].imag + fs.imag * fs0[i][j].real;
	    		*(output[i * m +j]) = out;
	    	}
	    }



}



/* complex -> complex */
void convultionInterpolation(complex **input, complex **output){

	// NOTE: <kx> is redefined because of a lack of proper support
	    // for global arrays; the array itself is too big to be fully
	    // unrolled since it leads to 1.4M lines of code and chokes gcc
	    float kx[n][m];
	    float kxmin = 1e25;
	    float kxmax = 0;

	    float dkx = PI / X0;
	    int   is  = 8;
	    int   I   = 2 * is + 1;

	    float kxs = (float) is * dkx;
	    float KX[nx];

	    int icKX[m];
	    int ikx[I][m];
	    float nKX[I][m];
	    float SINC[I][m];
	    float HAM[I][m];

	    complex F[nx][m];

	    /* init */
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

	    for (int i = 0; i < nx; i++) {
	    	KX[i] = kxmin + ((0 - is) - 2 + i) * dkx;
	    }


	    /* work */
	    for (int i = 0; i < n; i++) {
	    	for (int l = 0; l < I; l++) {
	    		for (int j = 0; j < m; j++) {
	    			icKX[j] = (int) round((kx[i][j] - KX[0]) / dkx) + 1;

	    			ikx[l][j] = icKX[j] + (l - is);
	    			ikx[l][j] = ikx[l][j] + (nx * j);

	    			nKX[l][j] = KX[(ikx[l][j] - 1) % nx];

	    			float x = (nKX[l][j] - kx[i][j]) / dkx;
	    			if (x == 0) {
	    				SINC[l][j] = 1;
	    			}
	    			else {
	    				SINC[l][j] = sin(PI * x) / (PI * x);
	    			}

	    			HAM[l][j] = 0.54 + (0.46 * cos((PI / kxs) * (nKX[l][j] - kx[i][j])));
	    		}
	    	}

	    	for (int j = 0; j < I; j++) {
	    		for(int l = 0; l < m; l++) {
	    			complex t = *(input[(i*m) + l]);

	    			int ri = (ikx[j][l] - 1) % nx;
	    			int ci = (ikx[j][l] - 1) / nx;

	    			F[ri][ci].real += t.real * SINC[j][l] * HAM[j][l];
	    			F[ri][ci].imag += t.imag * SINC[j][l] * HAM[j][l];
	    		}
	    	}
	    }

	    for (int j = 0; j < nx; j++) {
	    	for(int l = 0; l < m; l++) {
	    		*(output[j * m + l]) = F[j][l];
	    	}
	    }

}

/* complex->complex */
void compression(complex **input, complex **output){

    float cos_value[n][mc];
    float sin_value[n][mc];

    /* init */
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < mc; j++){
    		float value = 2 * (k[i] * (sqrt(pow(Xc, 2) + pow(uc[j], 2)) - Xc));

    		cos_value[i][j] = cos(value);
    		sin_value[i][j] = sin(value);
    	}
    }


    /* work */
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < mc; j++){
    		complex in = *(input[i * mc +j]);
    		complex out;

    		out.real =
    				(in.real * cos_value[i][j]) -
    				(in.imag * sin_value[i][j]);

    		out.imag =
    				(in.imag * cos_value[i][j]) +
    				(in.real * sin_value[i][j]);

    		*(output[i * mc +j]) = out ;
    	}
    }

}

/* complex->complex */
void decompression(complex **input, complex **output){

    float cos_value[n][m];
    float sin_value[n][m];

    /* init */
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < m; j++){
    		float value = 2 * (k[i] * (sqrt(pow(Xc, 2) + pow(u[j], 2)) - Xc));

    		cos_value[i][j] = cos(value);
    		sin_value[i][j] = sin(value);
    	}
    }


    /* work */
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < m; j++){
    		complex in = *(input[i * m +j]);
    		complex out;

    		out.real =
    				(in.real * cos_value[i][j]) +
    				(in.imag * sin_value[i][j]);

    		out.imag =
    				(in.imag * cos_value[i][j]) -
    				(in.real * sin_value[i][j]);

    		*(output[i *m +j])=out;
    	}
    }

}
#endif /* UTILS_HPP_ */
