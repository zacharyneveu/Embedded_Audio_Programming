/*
*	first order FIR filter:
*	y[n] = b0*x[n] + b1*x[n-1]
*
*/

#include <Bela.h>
#include <cstdlib>
#include <libraries/Scope/Scope.h>

// FIR coefficients
float b0 = 1;
float b1 = -1; 

float x_n_1 = 0; // previous input

float amp = 0.05; // audio output amplitude

Scope scope; // to plot the inout and the output signal


bool setup(BelaContext *context, void *userData)
{
	// prepare 2 channels on scope
	scope.setup(2, context->audioSampleRate); 

	return true;
}

void render(BelaContext *context, void *userData)
{
	// current input and output for first step
	float x_n;
	float y_n;
	
	// current input and output for second step
	float x2_n;
	float y2_n;
	
	float out;
	
	for(int n=0; n<context->audioFrames; n++)
	{
		// first step
		x_n = ( rand() / (float)RAND_MAX * 2 - 1); // input, white noise
		
		// implement filter
		//y_n = ...;
		
		// update previous input
		//x_n_1 = ...; 
		 
		 
		// plot signals on scope
		scope.log(x_n, y_n); // plot input and output

		// let's listen to the result
		out = amp*y_n; // attenuate level -> noise can be very annoying/dangerous!
		audioWrite(context, n, 0, out);
		audioWrite(context, n, 1, out);
	}
}

void cleanup(BelaContext *context, void *userData)
{

}