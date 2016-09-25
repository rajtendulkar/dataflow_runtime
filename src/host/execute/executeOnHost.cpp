/*
 * executeOnHost.cpp
 *
 *  Created on: Dec 30, 2013
 *      Author: rajtendulkar
 */

#include <executeOnHost.hpp>

ExecuteAppOnHost* executionPtr;

int getClusterId()
{
	return executionPtr->getClusterId();
}

int getProcId()
{
	return executionPtr->getProcId();
}

void *appExecThread (void *args)
{
	ApplicationData *appData = (ApplicationData*) args;
	int clusterId = getClusterId();
	int procId = getProcId();

	Schedule *schedule = appData->getSchedule(clusterId, procId);

	if(schedule != NULL)
	{
		for(unsigned int iter=0;iter<NUM_ITERATIONS;iter++)
		{
			for (unsigned int i=0;i<schedule->getScheduleSize();i++)
			{
				ActorInstance *actrInstance = schedule->getActorInstances(i);
				actrInstance->execute();
			}
		}
	}

	return 0;
}
