/***** Sampler.cpp *****/
#include "Sampler.h"
#include "sampleLoader.h"


Sampler::Sampler()
{
	numOfSamples = 0;
	samples = NULL;
	currentSampleIndex = 0;
	loop = true;
	isPlaying = false;
}


int Sampler::readFile(string fileName, int channel, float srate) 
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


float Sampler::process() 
{
	// if not playing (stopped), return sample = 0
	if(!isPlaying)
		return 0;
		
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
			isPlaying = false; // when at the end, just stop
		}
	}
	
	return currentSample;
}


void Sampler::setLoop(bool on) 
{
	loop = on;
}

// set to play from beginning
void Sampler::play(bool on) 
{
	isPlaying = on;
	currentSampleIndex = 0;
}

Sampler::~Sampler()
{
	if(samples != NULL)
		delete[] samples;
}