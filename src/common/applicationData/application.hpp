/*
 * application.h
 *
 *  Created on: Dec 30, 2013
 *      Author: rajtendulkar
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <schedule.hpp>
#include <applicationData.hpp>
#include <actorExecutor.hpp>
#include <actor.hpp>
#include <fifoUpdater.hpp>

class Application
{
public:
	virtual ~Application() {}
	virtual ActorExecutor* getActorExecutor(Actor *actor) = 0;
	virtual void initApplication (ApplicationData *appData) = 0;
	virtual void exitApplication (ApplicationData *appData) = 0;

	void resolveScheduleActorInstances (Schedule *schedule, ApplicationData *appData)
	{
		for (unsigned int i=0;i<schedule->getScheduleSize();i++)
		{
			ActorInstance *actrInstance = schedule->getActorInstances(i);
			Actor *actr = (Actor*)actrInstance->actor;
			assert (actr != NULL);
			ActorExecutor *actrExec = getActorExecutor(actr);
			if(actrExec == NULL)
			{
				cout << "Unable to Resolve Actor : " << *(actr->name) << endl;
				assert (actrExec != NULL);
			}

			actrInstance->executor = actrExec;
		}
	}
};

#endif /* APPLICATION_H_ */
