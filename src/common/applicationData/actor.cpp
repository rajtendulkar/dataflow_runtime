/*
 * actor.cpp
 *
 *  Created on: Jul 15, 2014
 *      Author: maselbas
 */

#include <actor.hpp>

#include <actorInstance.hpp>
#include <stdexcept>
#include <string>


Actor::Actor()
{
	name = NULL;
	instances = 0;
	numPorts = 0;
	channels = NULL;
	function = NULL;
	actorInstances = NULL;
}

Actor::Actor(char *actorName, char *function, unsigned int instances, unsigned int numPorts)
{
	this->name = new string(actorName);
	this->function = new string(function);
	this->instances = instances;
	this->numPorts = numPorts;
	channels = new Channel*[numPorts];
	for(unsigned int i=0;i<numPorts;i++)
		channels[i] = NULL;
	actorInstances = new ActorInstance*[instances];
	for(unsigned int i=0;i<instances;i++)
		actorInstances[i] = new ActorInstance(i, this);
}

Actor::~Actor()
{
	if(channels != NULL)
		delete [] channels;
	delete name;
	delete function;
	if(actorInstances != NULL)
	{
		for(unsigned int i=0;i<instances;i++)
			delete actorInstances[i];
		delete [] actorInstances;
	}
}

void Actor::setActorInstance(unsigned int numInstances)
{
	if((instances > 0) && (actorInstances != NULL))
	{
		for(unsigned int i=0;i<instances;i++)
			delete actorInstances[i];
		delete [] actorInstances;
	}

	instances = numInstances;
	actorInstances = new ActorInstance*[numInstances];
	for(unsigned int i=0;i<numInstances;i++)
		actorInstances[i] = new ActorInstance(i, this);
}

void Actor::print()
{
	cout << "Actor Name : " << *name << endl;
	cout << "\tNum Instances : " << instances << endl;
	cout << "\tNum Ports : " << numPorts << endl;
	for(unsigned int i=0;i<numPorts;i++)
		cout << "\tPort " << i << " : " << *(channels[i]->name) << endl;
}

Fifo *Actor::getFifo(unsigned int index)
{
	if(index >= numPorts)
		throw std::runtime_error("Index is Greater than Number of Ports\n");
	return channels[index]->fifo;
}

int Actor::getPortNumber (Channel *channel)
{
	for(unsigned int i=0;i<numPorts;i++)
		if(channels[i] == channel)
			return i;
	return -1;
}

Channel * Actor::getPort (unsigned int port)
{
	if(port >= numPorts)
		return NULL;
	return (channels[port]);
}

void Actor::setPort (unsigned int port, Channel *channel)
{
	if ((port >= numPorts) || (channels[port] != NULL))
	{
		cout << "Actor : " << *name << " Port :" << port << " Num Ports" << numPorts << " Channel " << channels[port] << endl;
		throw std::runtime_error("Ports Exceeded or Channel already filled.\n");
	}

	channels[port] = channel;
}

bool Actor::isInitialized ()
{
	if((instances == 0) && (numPorts == 0)) return false;
	else return true;
}

void Actor::setNumPorts(unsigned int numPorts)
{
	this->numPorts = numPorts;
	if(channels != NULL)
		delete [] channels;
	channels = new Channel*[numPorts];
	for(unsigned int i=0;i<numPorts;i++)
		channels[i] = NULL;
}

ActorInstance* Actor::getActorInstance(unsigned int instance){
	return actorInstances[instance];
}





