/*
 * applicationData.h
 *
 *  Created on: Dec 28, 2013
 *      Author: rajtendulkar
 */

#ifndef APPLICATIONDATA_HPP_
#define APPLICATIONDATA_HPP_

/*
 * applicationData.h
 *
 *  Created on: Dec 28, 2013
 *      Author: rajtendulkar
 */

#include <shared_defs.hpp>
#include <actor.hpp>
#include <channel.hpp>
#include <fifoInfo.hpp>
#include <schedule.hpp>

#include <cstdlib>

// Note : I decided to make different version of application data on compute cluster.
// this is because one cluster needs to know only of its schedule and not a global view.
// we can save some space and communication there.
class ApplicationData
{
private:
	unsigned int numActors;
	unsigned int numChannels;
	Actor *actors;
	Channel *channels;
	unsigned int enabledClusters[CLUSTER_COUNT];
	Schedule *schedule[CLUSTER_COUNT][PE_PER_CLUSTER];


public:
	ApplicationData()
	{
		numActors = 0;
		numChannels = 0;
		actors = NULL;
		channels = NULL;

		for(int i=0;i<CLUSTER_COUNT;i++){
			for(int j=0;j<PE_PER_CLUSTER;j++){
				schedule[i][j] = NULL;
			}
		}
	}

	ApplicationData (unsigned int numActors, unsigned int numChannels)
	{
		this->numActors = numActors;
		this->numChannels = numChannels;

		actors = new Actor[numActors];
		channels = new Channel[numChannels];

		for(int i=0;i<CLUSTER_COUNT;i++){
			for(int j=0;j<PE_PER_CLUSTER;j++){
				schedule[i][j] = NULL;

			}
		}
	}

	~ApplicationData ()
	{
		for(int i=0;i<CLUSTER_COUNT;i++){
			for(int j=0;j<PE_PER_CLUSTER;j++){
				if(schedule[i][j] != NULL)
					delete schedule[i][j];
			}
		}

		delete [] actors;
		delete [] channels;
	}

	void print()
	{
		cout << "**********************************" << endl;
		cout << "No. Of Actors : " << numActors << endl;
		for(unsigned int i=0;i<numActors;i++)
			actors[i].print();

		cout << "**********************************" << endl;

		cout << "No. Of Channels : " << numChannels << endl;
		for(unsigned int i=0;i<numChannels;i++)
			channels[i].print();

		cout << "**********************************" << endl;

		cout << "************ Schedule ************" << endl;

		for(int i=0;i<CLUSTER_COUNT;i++)
		{
			for(int j=0;j<PE_PER_CLUSTER;j++)
			{
				if (schedule[i][j] != NULL)
				{
					cout << "Schedule for Cluster " << i << " Processor " << j << endl;
					schedule[i][j]->print();
				}
			}
		}

		cout << "**********************************" << endl;

	}

	void getActorInstanceAllocation (string name, int instanceId, int *clusterId, int *procId, int *index)
	{
		for(int i=0;i<CLUSTER_COUNT;i++)
			for(int j=0;j<PE_PER_CLUSTER;j++)
			{
				Schedule *sched = schedule[i][j];
				if(sched != NULL)
				{
					if (sched->containsActor(name, instanceId))
					{
						*clusterId = i;
						*procId = j;
						*index = sched->getSchedIndex (name, instanceId);
						return;
					}
				}
			}

		*clusterId = -1;
		*procId = -1;
		*index = -1;
	}

	int getActorAllocationInCluster (char *name)
	{
		for(int i=0;i<CLUSTER_COUNT;i++)
			for(int j=0;j<PE_PER_CLUSTER;j++)
			{
				Schedule *sched = schedule[i][j];
				if(sched != NULL)
				{
					if (sched->containsActor(name))
						return i;
				}
			}

		return -1;
	}

	unsigned int *getEnabledClusters()
	{
		for(int i=0;i<CLUSTER_COUNT;i++)
		{
			enabledClusters[i] = 0;
			for(int j=0;j<PE_PER_CLUSTER;j++)
				if(schedule[i][j] != NULL)
				{
					enabledClusters[i] = 1;
					break;
				}
		}

		return enabledClusters;
	}

	unsigned int getChannelIndex(Channel *chnnl)
	{
		for(unsigned int i=0;i<numChannels;i++)
			if(chnnl == &(channels[i]))
				return i;
		return -1;
	}

	Channel *getChannel (unsigned int index)
	{
		if(index >= numChannels)
			return NULL;
		else
			return (&(channels[index]));
	}

	Channel *getChannel (string name)
	{
		for(unsigned int i=0;i<numChannels;i++)
		{
			if(channels[i].name->compare(name) == 0)
				return &(channels[i]);
		}

		return NULL;
	}

	Channel * getFreeChannel()
	{
		for(unsigned int i=0;i<numChannels;i++)
			if(channels[i].isInitialized() == false)
				return &(channels[i]);
		return NULL;
	}

	Actor * getFreeActor()
	{
		for(unsigned int i=0;i<numActors;i++)
			if(actors[i].isInitialized() == false)
				return & (actors[i]);
		return NULL;
	}

	unsigned int getActorIndex(Actor *actr)
	{
		for(unsigned int i=0;i<numActors;i++)
			if(actr == &(actors[i]))
				return i;
		return -1;
	}

	Actor *getActor (unsigned int index)
	{
		if(index >= numActors)
			return NULL;
		else
			return (&(actors[index]));
	}

	Actor * getActor (string name)
	{
		for(unsigned int i=0;i<numActors;i++)
			if(actors[i].name->compare(name) == 0)
				return &(actors[i]);
		return NULL;
	}

	//normal schedule
	Schedule * getSchedule (unsigned int clusterId, unsigned int procId)
	{
		return schedule[clusterId][procId];
	}

	void setSchedule (unsigned int clusterId, unsigned int procId, Schedule *schedule)
    {
        this->schedule[clusterId][procId] = schedule;
    }

	unsigned int getNumActors() const { return numActors; }

	void setNumActors(unsigned int numActors)
	{
		this->numActors = numActors;
		if(actors != NULL)
			delete actors;
		actors = new Actor[numActors];
	}

	unsigned int getNumChannels() const { return numChannels; }

	void setNumChannels(unsigned int numChannels)
	{
		this->numChannels = numChannels;
		if (channels != NULL)
			delete channels;
		channels = new Channel[numChannels];
	}

	void addFifoInfoToChannel (FifoInfo *fifoInfo)
	{
		for(unsigned int i=0;i<numChannels;i++)
		{
			if(channels[i].name->compare(*(fifoInfo->name)) == 0)
			{
				channels[i].fifoInfo = fifoInfo;
				return;
			}
		}
		cout << "Error : No Channel found for Fifo Info" << fifoInfo->name << endl;
		cout << "Fix the XML File !!" << endl;
		exit(0);
	}
};
#endif /* APPLICATIONDATA_HPP_ */
