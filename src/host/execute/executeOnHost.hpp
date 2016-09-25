/*
 * executeOnHost.h
 *
 *  Created on: Dec 29, 2013
 *      Author: rajtendulkar
 */

#ifndef EXECUTEONHOST_HPP_
#define EXECUTEONHOST_HPP_

#include <pthread.h>
#include <errno.h>
#include <assert.h>
#include <application.hpp>
#include <applicationData.hpp>
#include <schedule.hpp>

extern void resolveScheduleActorInstances (Schedule *schedule);
extern void *appExecThread (void *args);
extern Application * getApplication ();

class ExecuteAppOnHost;
extern ExecuteAppOnHost* executionPtr;
class ExecuteAppOnHost
{
private:
	Application *application;
	ApplicationData *appData;
	pthread_t threadId[CLUSTER_COUNT][PE_PER_CLUSTER];

public:

	int getClusterId()
	{
		pthread_t currentThread = pthread_self();
		for(int i=0;i<CLUSTER_COUNT;i++)
			for(int j=0;j<PE_PER_CLUSTER;j++)
				if(threadId[i][j] == currentThread)
					return i;
		return -1;
	}

	int getProcId()
	{
		pthread_t currentThread = pthread_self();
		for(int i=0;i<CLUSTER_COUNT;i++)
			for(int j=0;j<PE_PER_CLUSTER;j++)
				if(threadId[i][j] == currentThread)
					return j;
		return -1;
	}

	~ExecuteAppOnHost()
	{
		/*
		// Delete the actor instances
		for(unsigned int i=0; i < appData->getNumActors(); i++){
			Actor * actr = appData->getActor(i);
			for(unsigned int j=0;j<actr->instances;j++){
				delete actr->getActorInstance(j);
			}
		*/

		delete application;
	}

	ExecuteAppOnHost(ApplicationData *appData)
	{
		this->appData = appData;
		application = getApplication();
		executionPtr = this;

		// Initialize the FIFO.
		for(unsigned int i=0;i<appData->getNumChannels();i++)
		{
			Channel *channel = appData->getChannel(i);
			channel->initializeFifo();
		}

		// Resolve the actor instances in the Schedule.
		for(int i=0;i<CLUSTER_COUNT;i++)
			for(int j=0;j<PE_PER_CLUSTER;j++)
			{
				Schedule *schedule = appData->getSchedule(i,j);
				if(schedule != NULL)
					application->resolveScheduleActorInstances (schedule, this->appData);
			}

		// Initialize the application
		application->initApplication(appData);
		// Initialize the individual actor instances
		for(unsigned int i=0; i< appData->getNumActors(); i++){
			Actor *actr = appData->getActor(i);
			for(unsigned int j=0; j< actr->instances ; j++){
				ActorInstance* actrInstance = actr->getActorInstance(j);
				ActorExecutor *executor = actrInstance->executor;
				executor->init(actrInstance->instanceId);
			}
		}
	}

	void execute ()
	{
		// Spawn The threads.
		for(int i=0;i<CLUSTER_COUNT;i++)
		{
			for(int j=0;j<PE_PER_CLUSTER;j++)
			{
				Schedule *schedule = appData->getSchedule(i,j);
				if(schedule != NULL)
				{
					int status = EAGAIN;
					while (status == EAGAIN)
						status = pthread_create(&(threadId[i][j]), NULL, appExecThread, (void*)appData);
				}
			}
		}

		// Join the cluster threads.
		for(unsigned int i=0;i<CLUSTER_COUNT;i++)
		{
			for(int j=0;j<PE_PER_CLUSTER;j++)
			{
				Schedule *schedule = appData->getSchedule(i,j);
				if(schedule != NULL)
				{
					int status = pthread_join(threadId[i][j], NULL);
					assert(status == 0);
				}
			}
		}

		// Finish the application
		application->exitApplication(appData);
	}
};

#endif /* EXECUTEONHOST_HPP_ */
