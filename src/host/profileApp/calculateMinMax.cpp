/*
 * calculateMinMax.cpp
 *
 *  Created on: Jan 13, 2014
 *      Author: rajtendulkar
 */

#include <limits.h>
#include <stdint.h>
#include <cmath>

uint64_t calculateMin (unsigned int dataSize, uint64_t *data)
{
	uint64_t currentMin = LLONG_MAX;

	for(unsigned int j=0;j<dataSize;j++)
	{
		if(data[j] < currentMin)
			currentMin = data[j];
	}

	return currentMin;
}

uint64_t calculateMax (unsigned int dataSize, uint64_t *data)
{
	uint64_t currentMax = 0;

	for(unsigned int j=0;j<dataSize;j++)
	{
		if(data[j] > currentMax)
			currentMax = data[j];
	}

	return currentMax;
}

float calculateMean (unsigned int dataSize, uint64_t *data)
{
	uint64_t currentSum = 0;

	for(unsigned int j=0;j<dataSize;j++)
		currentSum += data[j];

	return (float)currentSum / dataSize;
}

float calculateStdDev (unsigned int dataSize, uint64_t *data)
{
	float currentMean = calculateMean (dataSize, data);
	uint64_t currentSquaredSum=0;

	for(unsigned int j=0;j<dataSize;j++)
		currentSquaredSum += ((data[j] - currentMean) * (data[j] - currentMean));

	currentSquaredSum /= dataSize;

	return sqrtf (currentSquaredSum);
}
