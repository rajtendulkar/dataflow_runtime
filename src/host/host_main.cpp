/*
 * host_main.cpp
 *
 *  Created on: Dec 28, 2013
 *      Author: rajtendulkar
 */

#include <iostream>
#include <cstdlib>
#include <shared_defs.hpp>
#include <parseXml.hpp>
#include <parameters.hpp>
#include <executeOnHost.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
	ParseXml xmlParser;
	char *inputXmlFile=(char*)DEFAULT_INPUT_XML_FILE;

	if(argc != 2)
	{
		cout << "invalid number of arguments" << endl;
		return -1;
	}

		inputXmlFile = argv[1];

	struct stat sb;
    if (stat(inputXmlFile, &sb) == -1)
    {
        cout << "The input XML File : " << inputXmlFile << " does not exist." << endl;
        exit(0);
    }

	// Parse the XML File.
	ApplicationData *appData = xmlParser.parseXml ((char*)inputXmlFile);
	assert (appData != NULL);

	// Check for valid Fifo Sizes.
	for(unsigned int i=0;i<appData->getNumChannels();i++)
	{
		Channel *channel = appData->getChannel(i);
		FifoInfo *fifoInfo = channel->fifoInfo;
		int fifoSize = fifoInfo->fifoSize;
		int srcRate = channel->srcPortRate;
		int dstRate = channel->dstPortRate;

		if((fifoInfo->sourceCluster != fifoInfo->destinationCluster) && (((fifoSize % srcRate) != 0) || ((fifoSize % dstRate) != 0)))
		{
			cout << "We don't support odd rates for the FIFO which has reader and writer in different clusters." << endl;
			delete appData;
			return 0;
		}
	}

	// Execute the Application on the Host Platform.
	// Note : We strictly need this to be a pointer. earlier i had an object,
	// and the problem is that the scope of object finishes after the
	// deletion of appData and destructor is called later. so we end up
	// calling freeing illegal memory as schedule no longer exists in the appData.
	// so thats why we need to preserve the deletion order of executeAppOnHost and appData.
	// this can be explicitly controlled with use of pointers only.

	// Execute the Application on the Host Platform.
	ExecuteAppOnHost *executeAppOnHost = new ExecuteAppOnHost(appData);
	executeAppOnHost->execute();
	delete executeAppOnHost;

	cout << "Finished Execution Application" << endl;
	delete appData;
	return 0;
}

