/***** FilePlayer.cpp *****/
#include "FilePlayer.h"
#include "sampleLoader.h"


FilePlayer::FilePlayer()
{
	numOfSamples = 0;
	samples = NULL;
	currentSampleIndex = 0;
	loop = true;
}


int FilePlayer::readFile(string fileName, int channel, float srate) 
{
	numOfSamples = getNumFrames(fileName);
	samples = new float[numOfSamples];
	
	if( getSamples(fileName, samples, 0, 0, numOfSamples) != 0 ) 
	{
		rt_printf("Couldn't load audio file \"%s\"\n", fileName.c_str());
		return -1;
	}
	
	rt_printf("Loaded audio file \"%s\" with %d frames (%.1f seconds)\n", 
    		   fileName.c_str(), numOfSamples, numOfSamples/srate);
    		   
	return numOfSamples;
}


float FilePlayer::process() 
{
	float currentSample = samples[currentSampleIndex];	
	
	currentSampleIndex++;
	if(currentSampleIndex >= numOfSamples) 
	{
		if(loop)
			currentSampleIndex = 0;
		else 
		{
			currentSampleIndex = numOfSamples;
			currentSample = 0;
		}
	}
	
	return currentSample;
}


void FilePlayer::setLoop(bool on) 
{
	loop = on;
}


void FilePlayer::restart()
{
	currentSampleIndex = 0;
}

FilePlayer::~FilePlayer()
{
	if(samples != NULL)
		delete[] samples;
}