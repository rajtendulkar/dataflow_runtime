/*
 * profile.hpp
 *
 *  Created on: Jan 13, 2014
 *      Author: rajtendulkar
 */

#ifndef PROFILE_HPP_
#define PROFILE_HPP_

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include <limits.h>
#include <cmath>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <fstream>

extern uint64_t calculateMin (unsigned int dataSize, uint64_t *data);
extern uint64_t calculateMax (unsigned int dataSize, uint64_t *data);
extern float calculateMean (unsigned int dataSize, uint64_t *data);
extern float calculateStdDev (unsigned int dataSize, uint64_t *data);

class Profile
{
public:
	bool printInstanceData;
private:
	ApplicationData *appData;
	unsigned int schedSize;
	uint64_t *profileMemory;
	// To feed to the Java Solver, we need one min, one max,  per actor. So
	// we need to converge values of all instances into one.
	float *actorMin;
	float *actorMax;
	float *actorMean;
	float *actorStdDev;

	float *fifoStartMin;
	float *fifoStartMax;
	float *fifoStartMean;
	float *fifoStartStdDev;

	float *fifoEndMin;
	float *fifoEndMax;
	float *fifoEndMean;
	float *fifoEndStdDev;

	unsigned int **profMemIndices;
	uint64_t latency[NUM_ITERATIONS];

	uint64_t period[NUM_ITERATIONS];

public:
	Profile(ApplicationData *appData)
	{
		this->appData = appData;
		 printInstanceData = false;

		actorMin = new float[appData->getNumActors()];
		actorMax = new float[appData->getNumActors()];
		actorMean = new float[appData->getNumActors()];
		actorStdDev = new float[appData->getNumActors()];

		fifoStartMin = new float[appData->getNumActors()];
		fifoStartMax = new float[appData->getNumActors()];
		fifoStartMean = new float[appData->getNumActors()];
		fifoStartStdDev = new float[appData->getNumActors()];

		fifoEndMin = new float[appData->getNumActors()];
		fifoEndMax = new float[appData->getNumActors()];
		fifoEndMean = new float[appData->getNumActors()];
		fifoEndStdDev = new float[appData->getNumActors()];

		schedSize = 0;
		for(unsigned int i=0;i<CLUSTER_COUNT;i++)
			for(unsigned int j=0;j<PE_PER_CLUSTER;j++)
			{
				Schedule *schedule = appData->getSchedule(i,j);
				if(schedule != NULL)
					schedSize += schedule->getScheduleSize();
			}

		profileMemory = new uint64_t [schedSize * PROFILE_DATA_SIZE];

		profMemIndices = new unsigned int * [appData->getNumActors()];
		for(unsigned int i=0;i<appData->getNumActors();i++)
			profMemIndices[i] = new unsigned int[appData->getActor(i)->instances];
	}

	~Profile()
	{
		delete [] profileMemory;
		delete [] actorMin;
		delete [] actorMax;
		delete [] actorMean;
		delete [] actorStdDev;

		delete [] fifoStartMin;
		delete [] fifoStartMax;
		delete [] fifoStartMean;
		delete [] fifoStartStdDev;

		delete [] fifoEndMin;
		delete [] fifoEndMax;
		delete [] fifoEndMean;
		delete [] fifoEndStdDev;

		for(unsigned int i=0;i<appData->getNumActors();i++)
			delete [] profMemIndices[i];
		delete [] profMemIndices;
	}

	void receiveProfileData()
	{
		unsigned int profCount = 0;
		for(unsigned int i=0;i<CLUSTER_COUNT;i++)
			for(unsigned int j=0;j<PE_PER_CLUSTER;j++)
			{
				Schedule *schedule = appData->getSchedule(i,j);
				if(schedule != NULL)
				{
					for(unsigned int k=0;k<schedule->getScheduleSize();k++)
					{
						ActorInstance* instance = schedule->getActorInstances(k);
						int actorIdx = appData->getActorIndex(instance->actor);
						int instanceId = instance->instanceId;

						unsigned int dataSize = PROFILE_DATA_SIZE_IN_BYTES;

						profMemIndices[actorIdx][instanceId] = profCount;
						void *dataPtr = (void*)&profileMemory[PROFILE_DATA_SIZE * profCount++];
						// Receive the profiling information on the Host
						HostDataTransfer::ioClusterToHostRx (dataPtr, &dataSize);
					}
				}
			}
	}

	void analyseProfileData()
	{
		FILE *rawFile = fopen("rawData.txt", "w+");
		assert (rawFile != NULL);

		uint64_t minStartTime[NUM_ITERATIONS];
		uint64_t maxStartTime[NUM_ITERATIONS];

		for(unsigned int i=0;i<NUM_ITERATIONS;i++)
		{
			minStartTime[i] = 0xFFFFFFFFFFFFFFFF;
			maxStartTime[i] = 0;
			latency[i] = 0;
			period[i] = 0;
		}

		for(unsigned int i=0;i<appData->getNumActors();i++)
		{
			Actor *actor = appData->getActor(i);
			unsigned int instances = actor->instances;

			// uint64_t *tempData = new uint64_t[instances * PROFILE_DATA_SIZE];

			uint64_t *fifoStart = new uint64_t[instances * NUM_ITERATIONS];
			uint64_t *actorExecute = new uint64_t[instances * NUM_ITERATIONS];
			uint64_t *fifoEnd = new uint64_t[instances * NUM_ITERATIONS];

			for(unsigned int j=0;j<instances;j++)
			{
				int clusterId, procId, procSchedIndex;
				appData->getActorInstanceAllocation (*(actor->name), j, &clusterId, &procId, &procSchedIndex);
				assert (clusterId != -1);
				assert (procId != -1);
				assert (procSchedIndex != -1);

				int schedIndex = profMemIndices[appData->getActorIndex(actor)][j];

				for(unsigned int k=0;k<NUM_ITERATIONS;k++)
				{
					int index = schedIndex*PROFILE_DATA_SIZE + k*4;

					fifoStart[j*NUM_ITERATIONS + k] 	= profileMemory[index+1] - profileMemory[index+0];
					actorExecute[j*NUM_ITERATIONS + k]  = profileMemory[index+2] - profileMemory[index+1];
					fifoEnd[j*NUM_ITERATIONS + k] 	    = profileMemory[index+3] - profileMemory[index+2];

					fprintf(rawFile, "actor : %s cluster : %d proc : %d procSchedIndex : %d instanceId : %d iteration : %d "
							"t0 : %lu t1 : %lu t2 : %lu t3 : %lu\n",
							actor->name->c_str(), clusterId, procId, procSchedIndex, j , k, profileMemory[index+0], profileMemory[index+1],
							profileMemory[index+2], profileMemory[index+3]);

					if (profileMemory[index+0] < minStartTime[k])
						minStartTime[k] = profileMemory[index+0];
					if (profileMemory[index+3] > maxStartTime[k])
						maxStartTime[k] = profileMemory[index+3];

					if (k+1<NUM_ITERATIONS){
						uint64_t temp = profileMemory[index+4] - profileMemory[index+1];
						              //+ profileMemory[index+4] - profileMemory[index+3];
						if ( temp > period[k])
							period[k] = temp;
					}
				}

				if (printInstanceData == true)
				{
					uint64_t actorInstMin = calculateMin (NUM_ITERATIONS, &(actorExecute[j*NUM_ITERATIONS]));
					uint64_t actorInstMax = calculateMax (NUM_ITERATIONS, &(actorExecute[j*NUM_ITERATIONS]));
					float actorInstMean = calculateMean (NUM_ITERATIONS, &(actorExecute[j*NUM_ITERATIONS]));
					float actorInstStdDev = calculateStdDev (NUM_ITERATIONS, &(actorExecute[j*NUM_ITERATIONS]));

					uint64_t fifoStartMin = calculateMin (NUM_ITERATIONS, &(fifoStart[j*NUM_ITERATIONS]));
					uint64_t fifoStartMax = calculateMax (NUM_ITERATIONS, &(fifoStart[j*NUM_ITERATIONS]));
					float fifoStartMean = calculateMean (NUM_ITERATIONS, &(fifoStart[j*NUM_ITERATIONS]));
					float fifoStartStdDev = calculateStdDev (NUM_ITERATIONS, &(fifoStart[j*NUM_ITERATIONS]));

					uint64_t fifoEndMin = calculateMin (NUM_ITERATIONS, &(fifoEnd[j*NUM_ITERATIONS]));
					uint64_t fifoEndMax = calculateMax (NUM_ITERATIONS, &(fifoEnd[j*NUM_ITERATIONS]));
					float fifoEndMean = calculateMean (NUM_ITERATIONS, &(fifoEnd[j*NUM_ITERATIONS]));
					float fifoEndStdDev = calculateStdDev (NUM_ITERATIONS, &(fifoEnd[j*NUM_ITERATIONS]));

					cout << endl;
					cout << "Actor :" << *(actor->name) << " instance : " << j << endl;
					cout << "Execution -> Min : " << actorInstMin << " Max : " << actorInstMax << " Mean : " << actorInstMean << " Std. Dev. " << actorInstStdDev << endl;
					cout << "Fifo Start -> Min : " << fifoStartMin << " Max : " << fifoStartMax << " Mean : " << fifoStartMean << " Std. Dev. " << fifoStartStdDev << endl;
					cout << "Fifo End -> Min : " << fifoEndMin << " Max : " << fifoEndMax << " Mean : " << fifoEndMean << " Std. Dev. " << fifoEndStdDev << endl;
					cout << endl;
				}
			}

			actorMin[i] 		= calculateMin 		(instances * NUM_ITERATIONS, actorExecute);
			actorMax[i] 		= calculateMax 		(instances * NUM_ITERATIONS, actorExecute);
			actorMean[i]		= calculateMean 	(instances * NUM_ITERATIONS, actorExecute);
			actorStdDev[i] 		= calculateStdDev 	(instances * NUM_ITERATIONS, actorExecute);

			fifoStartMin[i] 	= calculateMin 		(instances * NUM_ITERATIONS, fifoStart);
			fifoStartMax[i] 	= calculateMax 		(instances * NUM_ITERATIONS, fifoStart);
			fifoStartMean[i] 	= calculateMean 	(instances * NUM_ITERATIONS, fifoStart);
			fifoStartStdDev[i]	= calculateStdDev 	(instances * NUM_ITERATIONS, fifoStart);

			fifoEndMin[i] 		= calculateMin 		(instances * NUM_ITERATIONS, fifoEnd);
			fifoEndMax[i] 		= calculateMax 		(instances * NUM_ITERATIONS, fifoEnd);
			fifoEndMean[i] 		= calculateMean 	(instances * NUM_ITERATIONS, fifoEnd);
			fifoEndStdDev[i] 	= calculateStdDev 	(instances * NUM_ITERATIONS, fifoEnd);

			delete [] fifoStart;
			delete [] actorExecute;
			delete [] fifoEnd;
		}

		for(unsigned int i=0;i<NUM_ITERATIONS;i++)
			latency[i] = maxStartTime[i] - minStartTime[i];

		fclose (rawFile);
	}

	void printProfileData()
	{
		uint64_t latencyMin = calculateMin (NUM_ITERATIONS, latency);
		uint64_t latencyMax = calculateMax (NUM_ITERATIONS, latency);
		float latencyMean = calculateMean (NUM_ITERATIONS, latency);
		float latencyStdDev = calculateStdDev (NUM_ITERATIONS, latency);

		uint64_t periodMin = calculateMin (NUM_ITERATIONS-1, period);
		uint64_t periodMax = calculateMax (NUM_ITERATIONS-1, period);
		float periodMean = calculateMean (NUM_ITERATIONS-1, period);
		float periodStdDev = calculateStdDev (NUM_ITERATIONS-1, period);

		float throughputMin = 1.0/(float)periodMin;
		float throughputMax = 1.0/(float)periodMax;
		float throughputMean = 1.0/periodMean;

		cout << "*************************************************************************" << endl;
		for(unsigned int i=0;i<appData->getNumActors();i++)
		{
			Actor *actor = appData->getActor(i);
			cout << "Actor " << *(actor->name) << endl
				 << "\t Actor      Min : "
					<< actorMin[i] << " Max : " << actorMax[i] << " Avg : "
					<< actorMean[i] << " Std. Dev : " << actorStdDev[i] << endl;
			cout << "\t Fifo Start Min : " << fifoStartMin[i] << " Max : " << fifoStartMax[i] <<
					" Avg : " << fifoStartMean[i] << " Std. Dev : " <<  fifoStartStdDev[i] << endl;
			cout << "\t Fifo End   Min : " << fifoEndMin[i] << " Max : " << fifoEndMax[i] <<
								" Avg : " << fifoEndMean[i] << " Std. Dev : " <<  fifoEndStdDev[i] << endl;

		}
		cout << "*************************************************************************" << endl << endl;
		cout << "\t\t Application Latency " << endl << endl;
		cout << "Latency Min : " << latencyMin << " Max : " << latencyMax
			 << " Mean : " << latencyMean << " Std Dev. " << latencyStdDev << endl;
		cout << "*************************************************************************" << endl;

		cout <<  endl;
		cout << "\t\t Application Period " << endl << endl;
		cout << "Period  Min : " << periodMin << " Max : " << periodMax
			 << " Mean : " << periodMean << " Std Dev. " << periodStdDev << endl;
		cout << "*************************************************************************" << endl;

		cout <<  endl;
		cout << "\t\t Application ThroughPut " << endl << endl;
		cout << "ThroughPut Min : " << throughputMin << " Max : " << throughputMax
			 << " Mean : " << throughputMean << endl;
		cout << "*************************************************************************" << endl;

#ifdef CSV_OUTPUT
		
		ofstream csvfile;
		csvfile.open ("profileData.csv");
		/*
		csvfile << "Actor,actorMin,actorMax,actorAvg,actorStd,fifoStartMin,fifoStartMax," <<
				"fifoStartAvg,fifoStartStd,fifoEndMin,fifoEndMax,fifoEndMean,fifoEndStd,"<<
				"Application,latencyMin,latencyMax,latencyMean,latencyStd,periodMin,"<<
				"periodMax,periodMean,periodStd,throughputMin,throughputMax,throughputMean"<<endl;
		csvfile << " , , , , , , , , , , , , ,Application,"<<latencyMin<<","<<latencyMax<<","<<latencyMean<<","<<latencyStdDev<<","<<
				periodMin<<","<<periodMax<<","<<periodMean<<","<<periodStdDev<<","<<
				throughputMin<<","<<throughputMax<<","<<throughputMean<<endl;
		for(unsigned int i=0;i<appData->getNumActors();i++)
		{

			Actor *actor = appData->getActor(i);
			csvfile << *(actor->name) <<","<< actorMin[i]<<","<<actorMax[i]<<","<<actorMean[i]<<","<<actorStdDev[i]<<","<<
					fifoStartMin[i]<<","<<fifoStartMax[i]<<","<<fifoStartMean[i]<<","<<fifoStartMean[i]<<","<<
					fifoEndMin[i]<<","<<fifoEndMax[i]<<","<<fifoEndMean[i]<<","<<fifoEndStdDev[i]<<endl;

					}*/
		csvfile << "Application,latencyMin,latencyMax,latencyMean,latencyStd,periodMin,periodMax,periodMean,periodStd,throughputMin,throughputMax,throughputMean"<<endl;
		csvfile << "," << latencyMin<<","<<latencyMax<<","<<latencyMean<<","<<latencyStdDev<<","<<
				periodMin<<","<<periodMax<<","<<periodMean<<","<<periodStdDev<<","<<
				throughputMin<<","<<throughputMax<<","<<throughputMean<<endl;
		csvfile.close();
		cout << "generated CSV file." << endl;
#endif

	}

	void generateProfileXml(char *applicationXmlFile, char *outputXmlFile)
	{
		xmlDoc *doc = NULL;
		xmlNode *root_element = NULL;

		xmlLineNumbersDefault(1);
		xmlThrDefIndentTreeOutput(1);
		xmlKeepBlanksDefault(0);
		xmlThrDefTreeIndentString("    ");
		/*
		 * this initialize the library and check potential ABI mismatches
		 * between the version it was compiled for and the actual shared
		 * library used.
		 */
		LIBXML_TEST_VERSION



		/*parse the file and get the DOM */
		doc = xmlReadFile(applicationXmlFile, NULL, 0);

		/*Get the root element node */
		root_element = xmlDocGetRootElement(doc);

		// Scan the ApplicationData XML.
		modifyXmlNodes (root_element);


		// xmlIndentTreeOutput = 1;

		// Dumping document to a file
		// xmlSaveFormatFileEnc (PROFILE_XML_FILE, doc, "UTF-8", 1);
		xmlSaveFormatFile (outputXmlFile, doc, 1);

		/*free the document */
		xmlFreeDoc(doc);

		/*
		 *Free the global variables that may
		 *have been allocated by the parser.
		 */
		xmlCleanupParser();
	}

	void modifyXmlNodes (xmlNode *root_element)
	{
		xmlNode *startNode = NULL;
		xmlNode *mappingNode = NULL;

		// First we scan the unique graph node.
		for (xmlNode *cur_node = root_element; cur_node; cur_node = cur_node->next)
		{
			if ((cur_node->type == XML_ELEMENT_NODE) && (!xmlStrcmp(cur_node->name, (const xmlChar *)"mapping")))
			{
				mappingNode = cur_node;
				xmlNode *child_node = NULL;
				for (child_node = cur_node->children; child_node; child_node = child_node->next)
				{
					if ((child_node->type == XML_ELEMENT_NODE) && (!xmlStrcmp(child_node->name, (const xmlChar *)"graph")))
					{
						startNode = child_node;
						break;
					}
				}
			}
		}

		// Remove the Schedule Node.
		for (xmlNode *cur_node = startNode; cur_node; cur_node = cur_node->next)
		{
			if ((cur_node->type == XML_ELEMENT_NODE) && (!xmlStrcmp(cur_node->name, (const xmlChar *)"schedule")))
			{
				xmlNode *prev_node = cur_node->prev;
				xmlUnlinkNode (cur_node);
				xmlFreeNode(cur_node);
				cur_node = prev_node;
			}
		}

		// Remove the Fifo Allocation Node.
		for (xmlNode *cur_node = startNode; cur_node; cur_node = cur_node->next)
		{
			if ((cur_node->type == XML_ELEMENT_NODE) && (!xmlStrcmp(cur_node->name, (const xmlChar *)"fifoallocation")))
			{
				xmlNode *prev_node = cur_node->prev;
				xmlUnlinkNode (cur_node);
				xmlFreeNode(cur_node);
				cur_node = prev_node;
			}
		}

		xmlNode *sdfPropertyNode = xmlNewChild(mappingNode, NULL, BAD_CAST "sdfProperties", NULL);

		for(unsigned int i=0;i<appData->getNumActors();i++)
		{
			Actor *actor = appData->getActor(i);
			xmlNode *actorPropertyNode = xmlNewChild(sdfPropertyNode, NULL, BAD_CAST "actorProperties", NULL);
			xmlNewProp(actorPropertyNode, BAD_CAST "actor", BAD_CAST actor->name->c_str());
			xmlNode *execTimeNode = xmlNewChild(actorPropertyNode, NULL, BAD_CAST "executionTime", NULL);

			char myFloat[100];
			sprintf(myFloat, "%f", actorMin[i] + fifoStartMin[i] + fifoEndMin[i]);
			xmlNewProp(execTimeNode, BAD_CAST "min", BAD_CAST myFloat);
			sprintf(myFloat, "%f", actorMax[i] + fifoStartMax[i] + fifoEndMax[i]);
			xmlNewProp(execTimeNode, BAD_CAST "max", BAD_CAST myFloat);
			sprintf(myFloat, "%f", actorMean[i] + fifoStartMean[i] + fifoEndMean[i]);
			xmlNewProp(execTimeNode, BAD_CAST "mean", BAD_CAST myFloat);
			sprintf(myFloat, "%f", actorStdDev[i] + fifoStartStdDev[i] + fifoEndStdDev[i]);
			xmlNewProp(execTimeNode, BAD_CAST "stdDev", BAD_CAST myFloat);
		}
	}
};

#endif /* PROFILE_HPP_ */
