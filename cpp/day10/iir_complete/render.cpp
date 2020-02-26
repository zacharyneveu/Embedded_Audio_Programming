/*
*	first order IIR filter:
*	y[n] = b0*x[n] + b1*x[n-1] + a1*y[n-1]
*
*	with autoamtic coefficient calculation
*/

#include <Bela.h>
#include <cstdlib> // for RAND_MAX
#include <cmath> // for expf() 
#include <libraries/Scope/Scope.h>


Scope scope;

// IIR coefficients
float b0;
float b1;
float a1;

float x_n_1; // previous input
float y_n_1; // previous output

// possible filter type
enum filter_type
{
	low_pass, // 0
	high_pass // 1
};

// settings
filter_type filterType = low_pass; // type of filter, one of the two options
float fc = 500; // cut-off frequency [Hz]
float amp = 0.05; // audio output amplitude


// we dynamically compute the coefficients, according to the desired filter type and cut-off freq
bool computeCoefficients(filter_type type, float freq, int srate)
{
	if(type == low_pass) 
	{
		a1 = expf(-2 * (float)M_PI * freq/srate);
		b0 = 1 - a1;
		b1 = 0;
		return true;
	}
	else if(type == high_pass)
	{
		a1 = expf(-2 * (float)M_PI * freq/srate);
		b0 = (1 + a1)/2;
		b1 = -b0;
		return true;	
	}
	else
	{
		rt_printf("Filter type not supported!\n");
		return false;	
	}
}


bool setup(BelaContext *context, void *userData)
{
	// only one command wihtin the if-statement, so we can omit the scope -> { ... }
	if(!computeCoefficients(filterType, fc, context->audioSampleRate))
		return false;

	// set previous values to zero
	x_n_1 = 0;
	y_n_1 = 0;

	// prepare 2 channels on scope
	scope.setup(2, context->audioSampleRate); 

	// ready to go
	return true;
}

void render(BelaContext *context, void *userData)
{
	// current input and output
	float x_n;
	float y_n;
	
	float audioOut;
	
	for(int n=0; n<context->audioFrames; n++)
	{
		x_n = ( rand() / (float)RAND_MAX * 2 - 1); // input, white noise
		y_n = b0*x_n + b1*x_n_1 + a1*y_n_1; // ouput
		// update previous input and output
		x_n_1 = x_n;
		y_n_1 = y_n; 
		 
		// plot signals on scope
		scope.log(x_n, y_n); // plot input and output

		// let's listen to the result (second step output)
		audioOut = amp*y_n; // attenuate level -> noise can be very annoying/dangerous!
		audioWrite(context, n, 0, audioOut);
		audioWrite(context, n, 1, audioOut);
	}
}

void cleanup(BelaContext *context, void *userData)
{

}