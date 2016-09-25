/*
 * sarFFT.hpp
 *
 *  Created on: Jun 23, 2014
 *      Author: maselbas
 */

#ifndef FFT_HPP_
#define FFT_HPP_

#include <sarParams.hpp>

#ifdef SAR_APP

void transpose(complex **input, complex **output, const int row, const int col){
    for (int j = 0; j < col; j++){
        for (int i = 0; i < row; i++){
            *(output[j*row+i]) = *(input[i * col + j]);
        }
    }
}


void FFT1D(complex **input, complex **output, const int rows){

    float cos_value[rows];
    float sin_value[rows];

    /* init */
    for (int i = 0; i < rows; i++) {
    	cos_value[i] = cos(PI2 * (float)i / (float)rows);
    	sin_value[i] = sin(PI2 * (float)i / (float)rows);
    }

    /* work */
    complex temp;

    for (int i = 0; i < rows; i++) {
    	float real = 0;
    	float imag = 0;

    	for (int j = 0; j < rows; j++) {
    		int k = (i * j) % rows;

    		complex t = *(input[j]);
    		real += (t.real * cos_value[k]) + (t.imag * sin_value[k]);
    		imag += (t.imag * cos_value[k]) - (t.real * sin_value[k]);
    	}
    	temp.real = real;
    	temp.imag = imag;

    	*(output[i])=temp;

    }

}

void FFT1Dshift(complex **input, complex **output,const int rows){
    int rows_mid;

    /* init */
    if (rows % 2 == 1) {
    	rows_mid = (rows - 1) / 2;
    } else {
    	rows_mid = rows / 2;
    }


    /* work */
    for (int i = 0; i < rows; i++) {
    	complex t = *(input[rows_mid]);
    	*(output[i])= t;

    	if (++rows_mid == rows) {
    		rows_mid = 0;
    	}
    }

}

void FFT2Dshift(complex **input, complex **output, const int rows, const int cols){
    int rows_mid;
    int cols_mid;

    /* init */
    if (rows % 2 == 1) {
    	rows_mid = (rows - 1) / 2;
    } else {
    	rows_mid = rows / 2;
    }

    if (cols % 2 == 1) {
    	cols_mid = (cols - 1) / 2;
    } else {
    	cols_mid = cols / 2;
    }
    /* work */
    complex temp[rows][cols];
    for (int i = 0; i < rows; i++) {
    	for (int j = 0; j < cols; j++) {
    		temp[rows_mid][cols_mid] = *(input[i*cols +j]);

    		if (++cols_mid == cols) {
    			cols_mid = 0;
    		}
    	}

    	if (++rows_mid == rows) {
    		rows_mid = 0;
    	}
    }
    for (int i = 0; i < rows; i++) {
    	for (int j = 0; j < cols; j++) {
    		*(output[i*cols +j])=temp[i][j];
    	}
    }

}

void FFT2D(complex **input, complex **output,const int rows,const int cols){
    float cos_value[rows];
    float sin_value[rows];

    /* init */
    for (int i = 0; i < rows; i++) {
    	cos_value[i] = cos(PI2 * (float)i / (float)rows);
    	sin_value[i] = sin(PI2 * (float)i / (float)rows);
    }

    /* work */
    complex temp[rows][cols];

    for (int i = 0; i < cols; i++) {
    	for (int j = 0; j < rows; j++) {
    		float real = 0;
    		float imag = 0;

    		for (int k = 0; k < rows; k++) {
    			int l = (j * k) % rows;

    			complex t = *(input[k * cols + i]);

    			real += (t.real * cos_value[l]) + (t.imag * sin_value[l]);
    			imag += (t.imag * cos_value[l]) - (t.real * sin_value[l]);
    		}
    		temp[j][i].real = real;
    		temp[j][i].imag = imag;
    	}
    }

    for (int i = 0; i < rows; i++) {
    	for (int j = 0; j < cols; j++) {
    		*(output[i*cols + j]) = temp[i][j];
    	}
    }

}

void iFFT2D(complex **input, complex **output,const int rows, const int cols){
    float cos_value[rows];
    float sin_value[rows];

    /* init */
    for (int i = 0; i < rows; i++) {
    	cos_value[i] = cos(PI2 * (float)i / (float)rows);
    	sin_value[i] = sin(PI2 * (float)i / (float)rows);
    }

    /* work */
    complex temp[rows][cols];

    for (int i = 0; i < cols; i++) {
    	for (int j = 0; j < rows; j++) {
    		float real = 0;
    		float imag = 0;

    		for (int k = 0; k < rows; k++) {
    			int l = (j * k) % rows;

    			complex t = *(input[k * cols + i]);

    			real += (t.real * cos_value[l]) - (t.imag * sin_value[l]);
    			imag += (t.imag * cos_value[l]) + (t.real * sin_value[l]);
    		}
    		temp[j][i].real = real / (float)rows;
    		temp[j][i].imag = imag / (float)rows;
    	}
    }

    for (int i = 0; i < rows; i++) {
    	for (int j = 0; j < cols; j++) {
    		*(output[i*cols + j]) = temp[i][j];
    	}
    }

}

void FTX2D(complex **input, complex **output,const int rows, const int cols){
	complex **pipe1 = new complex*[rows * cols];
	complex **pipe2 = new complex*[rows * cols];
	for(int i=0; i<rows*cols; i++){
		pipe1[i] = new complex;
		pipe2[i] = new complex;
	}
	FFT2Dshift(input, pipe1, rows, cols);
	FFT2D(pipe1, pipe2, rows, cols);
	FFT2Dshift(pipe2, output, rows, cols);
	for(int i=0; i<rows*cols; i++){
		delete pipe1[i];
		delete pipe2[i];
	}
	delete[] pipe1;
	delete[] pipe2;
}

void iFTX2D(complex **input, complex **output,const int rows, const int cols){
	complex **pipe1 = new complex*[rows * cols];
	complex **pipe2 = new complex*[rows * cols];
	for(int i=0; i<rows*cols; i++){
		pipe1[i] = new complex;
		pipe2[i] = new complex;
	}

	FFT2Dshift(input, pipe1, rows, cols);
	iFFT2D(pipe1, pipe2, rows, cols);
	FFT2Dshift(pipe2, output, rows, cols);

	for(int i=0; i<rows*cols; i++){
		delete pipe1[i];
		delete pipe2[i];
	}
	delete[] pipe1;
	delete[] pipe2;
}

void FTY2D(complex **input, complex **output,const int rows, const int cols){

	complex **pipe1 = new complex*[rows * cols];
	complex **pipe2 = new complex*[rows * cols];
	for(int i=0; i<rows*cols; i++){
		pipe1[i] = new complex;
		pipe2[i] = new complex;
	}

	transpose(input,pipe1, rows, cols);
	FFT2Dshift(pipe1,pipe2, cols, rows);
	FFT2D(pipe2,pipe1, cols, rows);
	FFT2Dshift(pipe1,pipe2, cols, rows);
	transpose(pipe2,output,cols, rows);

	for(int i=0; i<rows*cols; i++){
		delete pipe1[i];
		delete pipe2[i];
	}
	delete[] pipe1;
	delete[] pipe2;
}

void iFTY2D(complex **input, complex **output,const int rows, const int cols){

	complex **pipe1 = new complex*[rows * cols];
	complex **pipe2 = new complex*[rows * cols];
	for(int i=0; i<rows*cols; i++){
		pipe1[i] = new complex;
		pipe2[i] = new complex;
	}


	transpose(input,pipe1, rows, cols);
	FFT2Dshift(pipe1,pipe2, cols, rows);
	iFFT2D(pipe2,pipe1, cols, rows);
	FFT2Dshift(pipe1,pipe2, cols, rows);
	transpose(pipe2,output,cols, rows);


	for(int i=0; i<rows*cols; i++){
		delete pipe1[i];
		delete pipe2[i];
	}
	delete[] pipe1;
	delete[] pipe2;
}


void FTX1D(complex **input, complex **output, int rows){
	complex **pipe1 = new complex*[rows];
	complex **pipe2 = new complex*[rows];
	for(int i=0; i<rows; i++){
		pipe1[i] = new complex;
		pipe2[i] = new complex;
	}

	FFT1Dshift(input,pipe1,rows);
	FFT1D(pipe1  ,  pipe2 ,rows);
	FFT1Dshift(pipe2,output,rows);

	for(int i=0; i<rows; i++){
		delete pipe1[i];
		delete pipe2[i];
	}
	delete[] pipe1;
	delete[] pipe2;
}

#endif /* SAR_APP */
#endif /* FFT_HPP_ */
