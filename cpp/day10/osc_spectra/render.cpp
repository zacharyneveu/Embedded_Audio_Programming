#include <Bela.h>
#include <cmath> // for sinf()
#include "libraries/Scope/Scope.h"

float freq_sine = 220; // Hz [A3 note]
float amp_sine = 0.2;
float phase_sine;

float freq_square = 49; // Hz [G2 note]
float amp_square = 0.05;
float phase_square;



float invSrate;

Scope scope;


float advancePhase(float ph, float f) 
{
	ph += 2.0 * M_PI * f * invSrate;
	if(ph > 2.0 * M_PI)
		ph -= 2.0 * M_PI;

	return ph;
}


bool setup(BelaContext *context, void *userData)
{
	invSrate = 1.0 / context->audioSampleRate;
	
	phase_sine = 0;
	phase_square = 0;

	scope.setup(2, context->audioSampleRate);
	
	return true;
}

void render(BelaContext *context, void *userData)
{
	float sample_sine;
	float sample_square;
	float out;
	
	for(unsigned int n = 0; n < context->audioFrames; n++) 
	{
		// sine
		sample_sine = amp_sine*sinf(phase_sine);
		phase_sine = advancePhase(phase_sine, freq_sine);
		
		// our new friend squarewave
		if(phase_square <= M_PI)
			sample_square = 1;
		else
			sample_square = 0;
		sample_square *= amp_square;
		phase_square = advancePhase(phase_square, freq_square);
		
		
		scope.log(sample_sine, sample_square);
		
		out = sample_sine+sample_square;
		
		audioWrite(context, n, 0, out);
		audioWrite(context, n, 1, out);

	}
}

void cleanup(BelaContext *context, void *userData)
{

}