#include <Bela.h>
#include <cstdlib> // for RAND_MAX
#include "NoiseOSC.h"
#include "libraries/Scope/Scope.h"

float amp = 0.05; // audio output amplitude, very quiet as noise can be very annoying (dangerous)

Scope scope; // to plot the signal, in the frequency domain
NoiseOSC osc;


bool setup(BelaContext *context, void *userData)
{
	// prepare 1 channels on scope
	scope.setup(1, context->audioSampleRate); 

	return true;
}

void render(BelaContext *context, void *userData)
{
	float noise_sample;
	float ns;
	
	for(int n=0; n<context->audioFrames; n++)
	{
		// first step
		noise_sample = rand(); // returns a pseudo-random number from 0 to RAND_MAX (built-in C++ variable)
		noise_sample /= RAND_MAX; // now random sample is between 0 and 1
		noise_sample = noise_sample*2 - 1; // finally random sample between -1 and 1 -> white noise! (kind of)

		ns = osc.process();

		scope.log(ns);
	
		audioWrite(context, n, 0, amp*ns);
		audioWrite(context, n, 1, amp*ns);
	}
}

void cleanup(BelaContext *context, void *userData)
{

}