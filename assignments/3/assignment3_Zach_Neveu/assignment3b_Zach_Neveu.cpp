#include <Bela.h>
#include <cmath> // for pow()
#include <cstdlib> // for RAND_MAX

#include <libraries/Oscillator/Oscillator.h>
#include "LP_Biquad.h"
#include "FilePlayer.h"

/**
 * Map from [-1, 1] range to a specified range
 * Params:
 * 	in 		(float)	: input value
 * 	inRange (*float): input range in form [min, max]
 * 	outRange(*float): output range in form [min, max]
 */
float map_to_range(float in, float* inRange, float *outRange)
{
	float o_range = outRange[1]-outRange[0];
	float i_range = inRange[1]-inRange[0];
	// subtract bias of old range, multiply by ratio, then add new bias
	return (in-inRange[0])*o_range/i_range + outRange[0];
}

float amp = 0.8; // if too soft, increase, but be careful!

// filter specifications
float filterFreq = 500.; // Hz
float filterQ = 0.01; // dimensionless
float QRange[2] = {0.01, 2.3};

float LFOFreq = 2.; // Hz
float FCRange[2] = {200, 2000};

float LowEndRange[2] = {0.1, 200};

// define starting ranges of signals
float SinInRange[] = {-1, 1};
// saw range inverted because saw waves going wrong direction
float SawInRange[] = {2, 0};

LP_Biquad stage1;
LP_Biquad stage2;

Oscillator LFO;
Oscillator QOSC;
Oscillator LowEnd;

FilePlayer fp;

bool setup(BelaContext *context, void *userData)
{


	// NOTE: see LP_Biquad.h for coefficient setting logic
	stage1.setup(context->audioSampleRate, filterFreq, filterQ);
	stage2.setup(context->audioSampleRate, filterFreq, filterQ);

	// setup file reading
	int nSamples = fp.readFile("progression.wav", 0, context->audioSampleRate);
	if(nSamples < 0)
		return false;
	fp.setLoop(true);

	// setup oscillators
	// sine by default
	LFO.setup(LFOFreq, context->audioSampleRate);

	LowEnd.setup(context->audioSampleRate/nSamples, 
		context->audioSampleRate,
		Oscillator::sawtooth,
		-M_PI);

	QOSC.setup(context->audioSampleRate/nSamples, 
		context->audioSampleRate,
		Oscillator::sawtooth,
		-M_PI);

	return true;
}

void render(BelaContext *context, void *userData)
{
	float in; // same as x_n[0], input for first stage
	float intermediate; // same as y_n[0]=x_n[1], output of first stage and input for the second one
	float out; // same as y_n[1], output of second stage
	
    for(unsigned int n = 0; n < context->audioFrames; n++) {

		in = fp.process();

		// calculate lfo and q samples
		float lowEndSamp = map_to_range(LowEnd.process(), SawInRange, LowEndRange);
		float lfoRange[] = {lowEndSamp, FCRange[1]};
		float lfoSamp = map_to_range(LFO.process(), SinInRange, lfoRange);
		float qSamp = map_to_range(QOSC.process(), SawInRange, QRange);

		// update filter coefficients
		stage1.setup(context->audioSampleRate, lfoSamp, qSamp);
		stage2.setup(context->audioSampleRate, lfoSamp, qSamp);

		// process samples
		// NOTE: See LP_Biquad.h for processing logic
		intermediate = stage1.process(in);
		out = stage2.process(intermediate);

		out *= amp;
            
        // write the outputs to the audio channels
		audioWrite(context, n, 0, out);
		audioWrite(context, n, 1, intermediate);
    }
}

void cleanup(BelaContext *context, void *userData)
{

}
