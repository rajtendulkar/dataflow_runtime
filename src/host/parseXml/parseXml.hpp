/*
 * parseXml.h
 *
 *  Created on: Dec 28, 2013
 *      Author: rajtendulkar
 */

#ifndef PARSEXML_H_
#define PARSEXML_H_

//#include "shared_defs.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <applicationData.hpp>

class ParseXml
{
private:
	ApplicationData* scanApplicationXml (xmlNode *root_element);
	int extractFifoAllocation (xmlNode *cur_node, ApplicationData *appData);

	int extractSchedule (xmlNode *cur_node, ApplicationData *appData);
	int extractClusterSchedule (xmlNode *cur_node, ApplicationData *appData, int clusterId);
	int extractProcessorSchedule(xmlNode *procSchednode, ApplicationData *appData, int &procId, Schedule **schedule);
	int extractProcessorSchedule (xmlNode *cur_node, ApplicationData *appData, int clusterId);

	int extractChannels (xmlNode *cur_node, ApplicationData *appData);
	int extractActors (xmlNode *cur_node, ApplicationData *appData);
	void freeAppDataStruct(ApplicationData** appDataPtr);
	int getIntegerValue(xmlNode *cur_node, char *property);
	char* getStringValue (xmlNode *cur_node, char *property);
	bool containsProperty(xmlNode *cur_node, char *property);
	xmlNode * getNode (xmlNode *nodeListPtr, char *nodeName);
	int countNumNodes (xmlNode *nodeListPtr, char *nodeName);

public:
	ApplicationData* parseXml (char *fileName);
};


#endif /* PARSEXML_H_ */
