/*
 * jpeg.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: rajtendulkar
 */


#include "jpeg.hpp"

#include <shared_defs.hpp>
#include <application.hpp>
#include <vld.hpp>
#include <color.hpp>
#include <iqidct.hpp>

#ifdef JPEG_DECODER

#include <decodeJpgHeader.hpp>
#include <fastIdct.hpp>
#include <generateBitmap.hpp>
#include <huffman.hpp>
#include <imageBuffer.hpp>
#include <parse.hpp>
#include <utils.hpp>

JpgParams jpgParams;
VldParams vldParams;
HuffTable huffTable;
unsigned char FrameBuffer[X_SIZE * Y_SIZE * 3];

class JpegApp : public Application
{
private:
	unsigned int fileSize;
	unsigned char *jpgImageData;

public:
	ActorExecutor * getActorExecutor(Actor *actor)
	{
		if(actor->function->compare("VLD") == 0)
			return new Vld(actor);
		else if(actor->function->compare("IQ") == 0)
			return new IqIdct(actor);
		else if(actor->function->compare("COLOR") == 0)
			return new Color(actor);
		else
			return NULL;
	}

	JpegApp()
	{
		jpgImageData = NULL;
		// Read the Jpeg File on Host.
		FILE * inputFp = fopen(INPUT_FILE_NAME, "r");
		if(inputFp == NULL)
		{
			cout << "Error opening the Input Jpg file " << INPUT_FILE_NAME << endl;
			exit(0);
		}

		// Determine the File Size to allocate the array.
		fileSize = 0;
		fseek(inputFp, 0, SEEK_END);
		fileSize = ftell(inputFp);
		rewind(inputFp);

		// Allocate the Memory for Input Image
		int dataSize = ((fileSize + (4 - (fileSize%4))) * sizeof(char));
		jpgImageData =  new unsigned char [dataSize];

		unsigned int bytesRead = fread(jpgImageData, sizeof(char), fileSize, inputFp);
		if(bytesRead != fileSize)
		{
			cout << "Error in reading bytes " << bytesRead << " :: " << fileSize << endl;
			exit(1);
		}

		fclose(inputFp);
	}

	~JpegApp()
	{
		delete [] jpgImageData;
	}

	void exitApplication (ApplicationData *appData)
	{
		// Let us write the bitmap output outside the application.
		generateBitmapFile(X_SIZE, Y_SIZE, FrameBuffer);
	}

	void initApplication (ApplicationData *appData)
	{
		decodeJpgHeader ((VldParams*)&vldParams, (JpgParams*)&jpgParams, (HuffTable*)&huffTable, jpgImageData);
	}
};


Application * getApplication ()
{
	return new JpegApp();
}
#endif /* JPEG_DECODER */
