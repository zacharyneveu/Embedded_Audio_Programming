#include <Bela.h>
#include "FilePlayer.h"

FilePlayer fp;

bool setup(BelaContext *context, void *userData)
{
	if (fp.readFile("waves.wav", 0, context->audioSampleRate) < 0)
	{
		return false;
	}
	

	return true;
}

void render(BelaContext *context, void *userData)
{
	float sample;
	for(int n=0; n<context->audioFrames; n++) 
	{
		sample = fp.process();
	
		audioWrite(context, n, 0, sample);
		audioWrite(context, n, 1, sample);
	}
}

void cleanup(BelaContext *context, void *userData)
{

}