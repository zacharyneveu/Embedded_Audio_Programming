/***** FilePlayer.cpp *****/
#include "FilePlayer.h"
#include "sampleLoader.h"


FilePlayer::FilePlayer()
{
	numOfSamples = -1;
	samples = NULL;
	currentSampleIndex = 0;
	loop = false;	
}


int FilePlayer::readFile(string fileName, int channel, float sampleRate) 
{
	numOfSamples = getNumFrames(fileName);
	samples = new float[numOfSamples];

	int retval = getSamples(fileName, samples, channel, 0, numOfSamples);

	if(retval == -1)
		return -1;
	else
	{
		rt_printf("Loaded file with duration %f [seconds]\n", numOfSamples/sampleRate);
	}
	
    		   
	return numOfSamples;
}


float FilePlayer::process() 
{
	float currentSample = samples[currentSampleIndex];

	++currentSampleIndex;
	if (currentSampleIndex >= numOfSamples)
	{
		currentSampleIndex = 0;
		if(!loop)
			return 0;
	}
	
	return currentSample;
}

void FilePlayer::setLoop(bool on)
{
	loop = on;
}



FilePlayer::~FilePlayer()
{
	if (samples != NULL)
	{
		delete samples;
	}
	

}