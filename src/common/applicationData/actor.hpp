/*
 * actor.h
 *
 *  Created on: Dec 28, 2013
 *      Author: rajtendulkar
 */

#ifndef _ACTOR_HPP
#define _ACTOR_HPP

#include <channel.hpp>

class ActorInstance;

class Actor
{
private:
	unsigned int numPorts;
	Channel **channels;
public:
	string *name;
	string *function;
	unsigned int  instances;
	ActorInstance **actorInstances;


	Actor();

	Actor(char *actorName, char *function, unsigned int instances, unsigned int numPorts);

	~Actor();

	void print();

	Fifo *getFifo(unsigned int index);

	int getPortNumber (Channel *channel);

	Channel * getPort (unsigned int port);

	void setPort (unsigned int port, Channel *channel);

	bool isInitialized ();

	unsigned int getNumPorts() const { return numPorts; }

	void setNumPorts(unsigned int numPorts);

	ActorInstance* getActorInstance(unsigned int instance);
	void setActorInstance(unsigned int numInstances);

};

#endif /* _ACTOR_HPP */
