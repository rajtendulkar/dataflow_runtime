/*
 * parseXml.cpp
 *
 *  Created on: Dec 28, 2013
 *      Author: rajtendulkar
 */

#include <parseXml.hpp>
#include <fifoInfo.hpp>

// Remember this function will return the first node which matches the node name.
// It will be good if you use this function only to detect the unique nodes.
// I mean top-level nodes, which will be only one per xml.
xmlNode * ParseXml::getNode (xmlNode *nodeListPtr, char *nodeName)
{
	for (xmlNode *cur_node = nodeListPtr; cur_node; cur_node = cur_node->next)
	{
		if ((cur_node->type == XML_ELEMENT_NODE) && (!xmlStrcmp(cur_node->name, (const xmlChar *)nodeName)))
			return cur_node;
	}

	cout << "Node " << nodeName << " is missing !" << endl;
	assert (0);
	return NULL;
}

int ParseXml::countNumNodes (xmlNode *nodeListPtr, char *nodeName)
{
	int count = 0;
	for (xmlNode *cur_node = nodeListPtr; cur_node; cur_node = cur_node->next)
	{
		if ((cur_node->type == XML_ELEMENT_NODE) && (!xmlStrcmp(cur_node->name, (const xmlChar *)nodeName)))
			count++;
	}
	return count;
}

bool ParseXml::containsProperty(xmlNode *node, char *property)
{
	for(xmlAttrPtr attr = node->properties; NULL != attr; attr = attr->next)
	{
		if ((!xmlStrcmp(attr->name, (const xmlChar *)property)))
			return true;
	}

	return false;
}

int ParseXml::getIntegerValue(xmlNode *node, char *property)
{
	for(xmlAttrPtr attr = node->properties; NULL != attr; attr = attr->next)
	{
		if ((!xmlStrcmp(attr->name, (const xmlChar *)property)))
			return atoi((char*)attr->children->content);
	}

	cout << "Property Missing : " << property << endl;
	assert (0);
	return -1;
}

char* ParseXml::getStringValue (xmlNode *node, char *property)
{
	for(xmlAttrPtr attr = node->properties; NULL != attr; attr = attr->next)
	{
		if ((!xmlStrcmp(attr->name, (const xmlChar *)property)))
			return (char*)attr->children->content;
	}

	cout << "Property Missing : " << property << endl;
	assert (0);
	return NULL;
}

int ParseXml::extractActors (xmlNode *actorListNode, ApplicationData *appData)
{
	int numActors = getIntegerValue(actorListNode, (char*)"size");
	appData->setNumActors(numActors);

	int actorsScanned=0;

	for (xmlNode *actorNode = actorListNode->children; actorNode; actorNode = actorNode->next)
	{
		if ((actorNode->type == XML_ELEMENT_NODE) && (!xmlStrcmp(actorNode->name, (const xmlChar *)"actor")))
		{

			Actor *actor = appData->getFreeActor();
			assert(actor != NULL);

			actor->name = new string(getStringValue(actorNode, (char*)"name"));
			actor->function = new string(getStringValue(actorNode, (char*)"function"));
			actor->instances = getIntegerValue(actorNode, (char*)"instances");
			actor->setNumPorts(getIntegerValue(actorNode, (char*)"numPorts"));
			actor->setActorInstance(actor->instances);
			actorsScanned++;

			assert (actorsScanned <= numActors);
		}
	}

	assert (numActors == actorsScanned);

	return 0;
}

int ParseXml::extractChannels(xmlNode *channelListNode, ApplicationData *appData)
{
	int numChannels = getIntegerValue(channelListNode, (char*)"size");
	appData->setNumChannels(numChannels);

	int channelsScanned=0;

	for (xmlNode *channelNode = channelListNode->children; channelNode; channelNode = channelNode->next)
	{
		if ((channelNode->type == XML_ELEMENT_NODE) && (!xmlStrcmp(channelNode->name, (const xmlChar *)"channel")))
		{

			Actor *srcActor, *dstActor;

			Channel *channel = appData->getFreeChannel();
			assert(channel != NULL);

			channel->name = new string(getStringValue(channelNode, (char*)"name"));
			channel->channelSize = (getIntegerValue(channelNode, (char*)"channelSize"));
			channel->tokenSize = (getIntegerValue(channelNode, (char*)"tokenSize"));

			if(containsProperty(channelNode, (char*)"initialTokens") == true)
				channel->initialTokens = (getIntegerValue(channelNode, (char*)"initialTokens"));

			channel->srcPortRate = (getIntegerValue(channelNode, (char*)"srcPortRate"));
			channel->dstPortRate = (getIntegerValue(channelNode, (char*)"dstPortRate"));

			if(containsProperty(channelNode, (char*)"peekRate") == true )
				channel->peekRate = (getIntegerValue(channelNode, (char*)"peekRate"));

			srcActor = appData->getActor(getStringValue(channelNode, (char*)"srcActor"));
			assert(srcActor != NULL);

			dstActor = appData->getActor(getStringValue(channelNode, (char*)"dstActor"));
			assert(dstActor != NULL);

			int srcPort = getIntegerValue(channelNode, (char*)"srcPort");
			int dstPort = getIntegerValue(channelNode, (char*)"dstPort");
			srcActor->setPort(srcPort, channel);
			dstActor->setPort(dstPort, channel);

			// Set the source and destination actors.
			channel->srcActor = (srcActor);
			channel->dstActor = (dstActor);
			channel->srcPort = srcPort;
			channel->dstPort = dstPort;

			channelsScanned++;
			assert (channelsScanned <= numChannels);
		}
	}

	assert (channelsScanned == numChannels);

	return 0;
}

/*
 * Extract any kind of Processor schedule
 */
int ParseXml::extractProcessorSchedule(xmlNode *procSchednode, ApplicationData *appData, int &procId, Schedule **schedule)
{
	procId = getIntegerValue(procSchednode, (char*)"id");
	int size = getIntegerValue(procSchednode, (char*)"size");

	*schedule = new Schedule(size);

	int scannedNodes = 0;
	for (xmlNode *sched_node = procSchednode->children; sched_node; sched_node = sched_node->next)
	{
		if ((sched_node->type == XML_ELEMENT_NODE) && (!xmlStrcmp(sched_node->name, (const xmlChar *)"actor")))
		{
			Actor *actr = appData->getActor(getStringValue(sched_node, (char*)"name"));
			assert (actr != NULL);
			//ActorInstance *actrInstance = new ActorInstance(getIntegerValue(sched_node, (char*)"instance"), actr);
			unsigned int inst = getIntegerValue(sched_node, (char*)"instance");
			(*schedule)->setActorInstance (actr->getActorInstance(inst), scannedNodes);
			//(*schedule)->setActorInstance(actr,scannedNodes);
			scannedNodes++;
			assert (scannedNodes <= size);
		}
	}

	if((scannedNodes != size))
	{
		cout << "Expected Proc Schedule Nodes : " << size << " Scanned : " << scannedNodes << endl;
		assert (scannedNodes == size);
	}

	return 0;
}

/*
 * extract Processor schedule
 * set schedule as normale schedule in AppData
 */
int ParseXml::extractProcessorSchedule(xmlNode *procSchednode, ApplicationData *appData, int clusterId){
	int procId;
	Schedule *schedule = NULL;
	extractProcessorSchedule(procSchednode, appData, procId, &schedule);
	appData->setSchedule(clusterId, procId, schedule);
	return 0;
}

/*
 * extract cluster normal schedule
 */
int ParseXml::extractClusterSchedule (xmlNode *clusterSchedNode, ApplicationData *appData, int clusterId)
{
	int schedSize = getIntegerValue(clusterSchedNode, (char*)"size");
	int scannedList = 0;
	for (xmlNode *sched_node = clusterSchedNode->children; sched_node; sched_node = sched_node->next)
	{
		if ((sched_node->type == XML_ELEMENT_NODE) && (!xmlStrcmp(sched_node->name, (const xmlChar *)"processor")))
		{
			extractProcessorSchedule (sched_node, appData, clusterId);
			scannedList ++;
			assert (scannedList <= schedSize);
		}
	}

	assert (scannedList == schedSize);
	return 0;
}

/*
 * extract normal schedule
 */
int ParseXml::extractSchedule (xmlNode *scheduleNodeList, ApplicationData *appData)
{
	int scheduleSize = getIntegerValue(scheduleNodeList, (char*)"size");
	int scannedSchedNodes = 0;

	for (xmlNode *sched_node = scheduleNodeList->children; sched_node; sched_node = sched_node->next)
	{
		if ((sched_node->type == XML_ELEMENT_NODE) && (!xmlStrcmp(sched_node->name, (const xmlChar *)"cluster")))
		{
			int clusterId = getIntegerValue(sched_node, (char*)"id");
			if (extractClusterSchedule (sched_node, appData, clusterId) != 0)
				return (-1);
			scannedSchedNodes++;
		}
	}

	assert (scannedSchedNodes == scheduleSize);
	return 0;
}

int ParseXml::extractFifoAllocation (xmlNode *fifoNodeList, ApplicationData *appData)
{
	int numFifo = getIntegerValue(fifoNodeList, (char*)"size");
	int fifoScanned=0;

	for (xmlNode *fifoNode = fifoNodeList->children; fifoNode; fifoNode = fifoNode->next)
	{
		if ((fifoNode->type == XML_ELEMENT_NODE) && (!xmlStrcmp(fifoNode->name, (const xmlChar *)"fifo")))
		{
			FifoInfo *fifo = new FifoInfo();
			fifo->name = new string(getStringValue(fifoNode, (char*)"name"));
			fifo->sourceCluster = (getIntegerValue(fifoNode, (char*)"srcCluster"));
			fifo->destinationCluster = (getIntegerValue(fifoNode, (char*)"dstCluster"));
			fifo->fifoSize = (getIntegerValue(fifoNode, (char*)"fifoSize"));

			if(containsProperty(fifoNode, (char*)"srcMaxWriters") == true)
				fifo->srcMaxWriters = (getIntegerValue(fifoNode, (char*)"srcMaxWriters"));
			if(containsProperty(fifoNode, (char*)"dstMaxWriters") == true)
				fifo->dstMaxWriters = (getIntegerValue(fifoNode, (char*)"dstMaxWriters"));
			if(containsProperty(fifoNode, (char*)"dstTokenPortalTag") == true)
				fifo->dstTokenPortalTag = (getIntegerValue(fifoNode, (char*)"dstTokenPortalTag"));
			if(containsProperty(fifoNode, (char*)"srcStatusPortalTag") == true)
				fifo->srcStatusPortalTag = (getIntegerValue(fifoNode, (char*)"srcStatusPortalTag"));

			appData->addFifoInfoToChannel(fifo);
			fifoScanned++;
			assert (fifoScanned <= numFifo);
		}
	}

	assert (numFifo == fifoScanned);
	return 0;
}

ApplicationData* ParseXml::scanApplicationXml (xmlNode *root_element)
{
	ApplicationData *appData = new ApplicationData();

	// make sure these are unique nodes in the XML.
	assert (countNumNodes(root_element, (char*)"mapping") == 1);
	xmlNode *mappingNode = getNode (root_element, (char *)"mapping");

	// make sure these are unique nodes in the XML.
	assert (countNumNodes(mappingNode->children, (char*)"graphActors") == 1);
	assert (countNumNodes(mappingNode->children, (char*)"graphChannels") == 1);
	assert (countNumNodes(mappingNode->children, (char*)"schedule") == 1);
	assert (countNumNodes(mappingNode->children, (char*)"fifoallocation") == 1);

	xmlNode *graphActorsNode = getNode (mappingNode->children, (char *)"graphActors");
	xmlNode *graphChannelsNode = getNode (mappingNode->children, (char *)"graphChannels");
	xmlNode *scheduleNode = getNode (mappingNode->children, (char *)"schedule");
	xmlNode *fifoNode = getNode (mappingNode->children, (char *)"fifoallocation");

	// Now we have to scan the unique nodes
	if ((extractActors (graphActorsNode, appData) != 0))
		return (NULL);

	if ((extractChannels (graphChannelsNode, appData) != 0))
		return (NULL);

	if ((extractSchedule (scheduleNode, appData) != 0))
		return (NULL);

	if ((extractFifoAllocation (fifoNode, appData) != 0))
		return (NULL);

	return appData;
}

ApplicationData * ParseXml::parseXml(char *fileName)
{
	xmlDoc *doc = NULL;
	xmlNode *root_element = NULL;
	/*
	 * this initialize the library and check potential ABI mismatches
	 * between the version it was compiled for and the actual shared
	 * library used.
	 */
	LIBXML_TEST_VERSION

	/*parse the file and get the DOM */
	doc = xmlReadFile(fileName, NULL, 0);

	/*Get the root element node */
	root_element = xmlDocGetRootElement(doc);

	// Scan the ApplicationData XML.
	ApplicationData *appData = scanApplicationXml (root_element);

	/*free the document */
	xmlFreeDoc(doc);

	/*
	 *Free the global variables that may
	 *have been allocated by the parser.
	 */
	xmlCleanupParser();

	return appData;
}
