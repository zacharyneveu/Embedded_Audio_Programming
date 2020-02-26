/*
*	second order IIR filter:
*	y[n] = b0*x[n] + b1*x[n-1] + b2*x[n-2] + a1*y[n-1] + a2*y[n-2]
*
*	used twice in cascade (2 stage filtering)
*
*	with automatic low-pass coefficient calculation
*/

#include <Bela.h>
#include <cmath> // for pow()
#include <cstdlib> // for RAND_MAX
// add Scope library
#include <libraries/Scope/Scope.h>
#include "LP_Biquad.h"
#include <iostream>

float amp = 1; // if too soft, increase, but be careful!

// filter specifications
float filterFreq = 500.; // Hz
float filterQ = 4.; // dimensionless

Scope sc;
LP_Biquad stage1;
LP_Biquad stage2;

bool setup(BelaContext *context, void *userData)
{
	sc.setup(3, context->audioSampleRate);

	// NOTE: see LP_Biquad.h for coefficient setting logic
	stage1.setup(context->audioSampleRate, filterFreq, filterQ);
	stage2.setup(context->audioSampleRate, filterFreq, filterQ);

	return true;
}

void render(BelaContext *context, void *userData)
{
	float in; // same as x_n[0], input for first stage
	float intermediate; // same as y_n[0]=x_n[1], output of first stage and input for the second one
	float out; // same as y_n[1], output of second stage
	
    for(unsigned int n = 0; n < context->audioFrames; n++) {
		// NOTE: See LP_Biquad.h for processing logic

    	// read the next noise sample
		in = ( rand() / (float)RAND_MAX * 2 - 1); // input, white noise
		intermediate = stage1.process(in);
		out = stage2.process(intermediate);

        // send input and output (stage 2 output) samples to scope
		sc.log(in, intermediate, out);

		out *= amp;
            
        // write the outputs to the audio channels
		audioWrite(context, n, 0, out);
		audioWrite(context, n, 1, out);
    }
}

void cleanup(BelaContext *context, void *userData)
{

}
