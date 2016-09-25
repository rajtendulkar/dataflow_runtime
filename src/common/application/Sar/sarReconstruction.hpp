/*
 * sarReconstruction.hpp
 *
 *  Created on: Jun 24, 2014
 *      Author: maselbas
 */

#ifndef SARRECONSTRUCTION_HPP_
#define SARRECONSTRUCTION_HPP_

#include <sarParams.hpp>
#include <utils.hpp>
#include <FFT.hpp>

#ifdef SAR_APP

class Reconstruction : public ActorExecutor {
private:
public:
	Reconstruction (Actor *actor) : ActorExecutor(actor) {}

	void init (unsigned int instanceId) {}

	void execute (unsigned int instanceId, unsigned int iterationId){
		cout << "\t>>> Reconstruction init ..." << endl;

		complex **dataIn = (complex **)getFifoData(0);
		float ** dataOut = (float **)getFifoData(1);

		complex **pipe0 = new complex*[n * m];
		complex **pipe1 = new complex*[nx * m];
		complex **pipe2 = new complex*[nx * m];
		float   **pipef = new float*[nx * m];
		for(int i = 0; i < m ; i++){
			for(int j = 0; j < n; j++){
				pipe0[i*n+j] = new complex;
			}
			for(int j=0; j<nx; j++){
				pipe1[i*nx+j] = new complex;
				pipe2[i*nx+j] = new complex;
				pipef[i*nx+j] = new float;
			}
		}

		cout << "\t>>> Reconstruction executing ..." << endl;

		matchedFiltering(dataIn, pipe0);
		cout << "\t\tReconstruction done : matchedFiltering" << endl;

		convultionInterpolation(pipe0, pipe1);
		cout << "\t\tReconstruction done : convultionInterpolation" << endl;

		iFTX2D(pipe1, pipe2, nx, m);
		cout << "\t\tReconstruction done : iFTX2D" << endl;

		iFTY2D(pipe2, pipe1, nx, m);
		cout << "\t\tReconstruction done : iFTY2D" << endl;

		complexAbsoluate(pipe1, pipef, nx*m);
		cout << "\t\tReconstruction done : complexAbsoluate" << endl;

		floatTranspose( pipef, dataOut, nx, m);
		cout << "\t\tReconstruction done : floatTranspose" << endl;

		cout << "\t<<< Reconstruction done" << endl;

		for(int i = 0; i < m ; i++){
			for(int j = 0; j < n; j++){
				delete pipe0[i*n +j];
			}
			for(int j=0; j<nx; j++){
				delete pipe1[i*nx+j];
				delete pipe2[i*nx+j];
				delete pipef[i*nx+j];
			}
		}
		delete[] pipe0;
		delete[] pipe1;
		delete[] pipe2;
		delete[] pipef;

	}

};

#endif /* SAR_APP */

#endif /* SARRECONSTRUCTION_HPP_ */
