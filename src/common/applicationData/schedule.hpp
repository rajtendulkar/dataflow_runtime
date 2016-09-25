/*
 * schedule.h
 *
 *  Created on: Dec 28, 2013
 *      Author: rajtendulkar
 */

#ifndef SCHEDULE_HPP_
#define SCHEDULE_HPP_

#include <actorInstance.hpp>
#include <shared_defs.hpp>

class Schedule
{
private :
#ifdef __FRAMEWORK_HOST
	unsigned int clusterId;
	unsigned int processorId;
#endif /* __FRAMEWORK_HOST */
	unsigned int scheduleSize;
	ActorInstance **actorInstances;

public:
	Schedule(unsigned int scheduleSize)
	{
#ifdef __FRAMEWORK_HOST
		this->clusterId = -1;
		this->processorId = -1;
#endif /* __FRAMEWORK_HOST */
		this->scheduleSize = scheduleSize;
		actorInstances = new ActorInstance*[scheduleSize];
		for (unsigned int i=0;i<scheduleSize;i++)
			actorInstances[i] = NULL;
	}

	~Schedule()
	{
		delete [] actorInstances;
	}

	void print ()
	{
		cout << "\tSchedule Size : " << scheduleSize << endl;
		for (unsigned int i=0;i<scheduleSize;i++)
			actorInstances[i]->print();
	}

	bool containsActor (string name, unsigned int instanceId)
	{
		for(unsigned int i=0;i<scheduleSize;i++)
			if ((actorInstances[i]->instanceId == instanceId) &&
					(actorInstances[i]->actor->name->compare(name) == 0))
				return true;
		return false;
	}

	bool containsActor (string name)
	{
		for(unsigned int i=0;i<scheduleSize;i++)
			if(actorInstances[i]->actor->name->compare(name) == 0)
				return 1;

		return 0;
	}

	int getSchedIndex (string name, unsigned int instanceId)
	{
		for(unsigned int i=0;i<scheduleSize;i++)
			if ((actorInstances[i]->actor->name->compare(name) == 0) &&
					(actorInstances[i]->instanceId == instanceId))
				return i;

		return -1;
	}

	ActorInstance* getActorInstances(int index) { return (actorInstances[index]); }

	void setActorInstance (ActorInstance* actorInstance, unsigned int index)
	{
		actorInstances[index] = actorInstance;
	}

	unsigned int getScheduleSize() const { return scheduleSize; }


#ifdef __FRAMEWORK_HOST
	void setClusterId(unsigned int clusterId) { this->clusterId = clusterId; }
	unsigned int getProcessorId() const { return processorId; }
	void setProcessorId(unsigned int processorId) { this->processorId = processorId; }
	// unsigned int getClusterId() { return clusterId; }
#endif /* __FRAMEWORK_HOST */
};

#endif /* SCHEDULE_HPP_ */
