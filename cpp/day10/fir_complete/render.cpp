/*
*	first order FIR filter:
*	y[n] = b0*x[n] + b1*x[n-1]
*
*	used twice in cascade (2 step filtering)
*/

#include <Bela.h>
#include <cstdlib>
#include <libraries/Scope/Scope.h>

// FIR coefficients
float b0 = 1;
float b1 = 1; // 1 for LP, -1 for HP

float x_n_1[2] = {0, 0}; // previous input, first step

float amp = 0.05; // audio output amplitude

Scope scope; // to plot the signal, in the frequency domain


bool setup(BelaContext *context, void *userData)
{
	// prepare 3 channels on scope
	scope.setup(3, context->audioSampleRate); 

	return true;
}

void render(BelaContext *context, void *userData)
{
	// current input and output for first step
	float x_n;
	// current output for first and second step
	float y_n[2];
	
	float out;
	
	for(int n=0; n<context->audioFrames; n++)
	{
		// first step
		x_n = ( rand() / (float)RAND_MAX * 2 - 1); // input, white noise
		y_n[0] = b0*x_n + b1*x_n_1[0]; // ouput
		x_n_1[0] = x_n; // update previous input
		 
		// second step, same logic
		y_n[1] = b0*y_n[0] + b1*x_n_1[1]; // input is output of first step
		x_n_1[1] = y_n[0]; // update previous input for second step
		
		// plot signals on scope
		scope.log(x_n, y_n[0], y_n[1]); // plot input, output of first and output of second step

		// let's listen to the result (second step output)
		out = amp*y_n[1]; // attenuate level -> noise can be very annoying/dangerous!
		audioWrite(context, n, 0, out);
		audioWrite(context, n, 1, out);
	}
}

void cleanup(BelaContext *context, void *userData)
{

}