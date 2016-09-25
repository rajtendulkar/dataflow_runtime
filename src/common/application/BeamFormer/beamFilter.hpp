/*
 * beamFilter.hpp
 *
 *  Created on: Jan 6, 2014
 *      Author: rajtendulkar
 */

#ifndef BEAMFILTER_HPP_
#define BEAMFILTER_HPP_

#include <beamformerParams.hpp>

#ifdef BEAM_FOMER

class BeamFirFilter : public ActorExecutor
{
private :
    float *real_weight;
    float *imag_weight;
    float *realBuffer;
    float *imagBuffer;
    int numTapsMinusOne;
    int count;
    int pos;

    int numIterations;
    int numInstances;

    // Store these params for execution.
    int numTaps;
    int inputLength;
    int decimationRatio;

public:
    BeamFirFilter (Actor *actor) : ActorExecutor(actor)
    {
    	// Reset all the variables.
        real_weight = NULL;
        imag_weight = NULL;
        realBuffer = NULL;
        imagBuffer = NULL;
        numTapsMinusOne = 0;
        count = 0;
        pos = 0;
        numTaps = 0;
        inputLength = 0;
        decimationRatio = 0;
        numIterations = 0;
        numInstances  = 0;
    }

    ~BeamFirFilter()
    {
    	delete [] real_weight;
    	delete [] imag_weight;
    	delete [] realBuffer;
    	delete [] imagBuffer;
    }

    void init (unsigned int instanceId, int numTaps, int inputLength, int decimationRatio)
    {
    	real_weight = new float [numTaps];
    	imag_weight = new float [numTaps];
    	realBuffer  = new float [numTaps];
    	imagBuffer  = new float [numTaps];

        numTapsMinusOne = numTaps - 1;
        pos = 0;

        for (int j = 0; j < numTaps; j++)
        {
            int idx = j + 1;
            real_weight[j] = sin (idx) / ((float) idx);
            imag_weight[j] = cos (idx) / ((float) idx);
            realBuffer[j] = 0;
            imagBuffer[j] = 0;
        }

        this->numTaps = numTaps;
        this->inputLength = inputLength;
        this->decimationRatio = decimationRatio;
    }

    void init (unsigned int instanceId)
    {
    	numIterations=1;
    	// Case 1
    	if(actor->name->compare("BeamFirFilter0") == 0)
    	{
    		// cout << "Init BeamFirFilter0 : " << instanceId  << " :: " << COARSE_DECIMATION_RATIO << endl;
    		init (instanceId, NUM_COARSE_FILTER_TAPS, NUM_SAMPLES, COARSE_DECIMATION_RATIO);
    		numIterations=2;
    		numInstances = 12;
    	}
    	// Case 2
    	else if(actor->name->compare("BeamFirFilter1") == 0)
    	{
    		// cout << "Init BeamFirFilter1 : " << instanceId  << " :: " << FINE_DECIMATION_RATIO << endl;
    		init (instanceId, NUM_FINE_FILTER_TAPS, NUM_POST_DEC1, FINE_DECIMATION_RATIO);
    		numInstances = 12;
    	}
    	// Case 3
    	else if(actor->name->compare("BeamFirFilter2") == 0)
    	{
    		// cout << "Init BeamFirFilter2 : " << instanceId << " :: " << 1 << endl;
    		init (instanceId, MF_SIZE, NUM_POST_DEC2, 1);
    		numInstances = 4;
    	}
    	else
    	{
    		cout << "Invalid input actor : " << actor->name << endl;
    		exit(0);
    	}
    }

    void execute (unsigned int instanceId, unsigned int iterationId)
    {
    	float **inputData  = (float**)getFifoData(0);
    	float **outputData = (float**)getFifoData(1);
        float real_curr = 0;
        float imag_curr = 0;
        int modPos;

        for(int iter=0;iter<numIterations;iter++)
        {
        	real_curr = 0;
        	imag_curr = 0;
			realBuffer[numTapsMinusOne - pos] = *(inputData[iter*2+0]);
			imagBuffer[numTapsMinusOne - pos] = *(inputData[iter*2+1]);
			modPos = numTapsMinusOne - pos;

			for (int i = 0; i < numTaps; i++)
			{
				// if(strcmp(actor->getName(), "BeamFirFilter1") == 0 && instanceId == 0)
				//	cout << "I:" << i << " real : " << real_curr << " Imag : " << imag_curr << " " <<
				//		modPos << " " << realBuffer[modPos] << " " << real_weight[i] << " " << imagBuffer[modPos] << " " <<  imag_weight[i] << endl;
				real_curr += realBuffer[modPos] * real_weight[i] + imagBuffer[modPos] * imag_weight[i];
				imag_curr += imagBuffer[modPos] * real_weight[i] + realBuffer[modPos] * imag_weight[i];
				modPos = (modPos + 1) & numTapsMinusOne;
			}

//			if(strcmp(actor->getName(), "BeamFirFilter1") == 0)
//			{
//				// cout << "input" << iter << " "<<  *(inputData[iter*2+0]) << " " <<  *(inputData[iter*2+1]) << endl;
//				cout << "Id : " << instanceId << " pos : " << pos << " real : " << realBuffer[numTapsMinusOne - pos] <<
//				        		" imag : " << imagBuffer[numTapsMinusOne - pos] << " op : " << real_curr << " " << imag_curr << endl;
//			}

			pos = (pos + 1) & numTapsMinusOne;
			*(outputData[iter*2+0]) = real_curr;
			*(outputData[iter*2+1]) = imag_curr;

			count += decimationRatio;

			if (count == inputLength)
			{
				count = 0;
				pos = 0;
				for (int i = 0; i < numTaps; i++)
				{
					realBuffer[i] = 0;
					imagBuffer[i] = 0;
				}
			}
        }
    }
};

#endif /* BEAM_FOMER */
#endif /* BEAMFILTER_HPP_ */
