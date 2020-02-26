/*
 * Copyright (C) 2020 zach zachary.neveu@gmail.com
 */

#include <Bela.h>
#include <cmath>
#include <random>
#include <stdlib.h>
#include <libraries/Biquad/Biquad.h>
#include "utils.h"


// Globals
float invSr;
float freq_sin = 250; // osc freq in Hz
float phase_sin = 0;
float amp_sin = db2amp(-10);

float freq_sq = 125;
float phase_sq = 0;
float amp_sq = db2amp(-10);

Biquad lpFilter;
float gLPfreq = 2000.0; // 2k lpf on noise
float gFilterQ = sqrt(2);


// Return true if all goes well
bool setup(BelaContext *context, void *userData)
{
    invSr = 1/context->audioSampleRate;

    lpFilter.setup(gLPfreq, context->audioSampleRate, Biquad::lowpass, gFilterQ, 0);
	return true;
}

// Triggered by audio interface interrupt
// returns an array of size Block_Size x n_channels
void render(BelaContext *context, void *userData)
{
    float sample;

    for (int i = 0; i < context->audioFrames; i++)
    {
        sample = 0;
////////////////////////////////////////////////////////////////////////////////
//      Sine wave oscillator
////////////////////////////////////////////////////////////////////////////////
        sample += sinf(phase_sin) * amp_sin;
        // sample *= amp2db(-10);
        phase_sin += freq_sin*2*M_PI*invSr;
        phase_sin = phase_sin > 2*M_PI ? phase_sin - 2*M_PI : phase_sin;
////////////////////////////////////////////////////////////////////////////////
//      Noise Oscillator
////////////////////////////////////////////////////////////////////////////////
        sample += noise(-25);
        sample = lpFilter.process(sample);

////////////////////////////////////////////////////////////////////////////////
//      Square wave oscillator
////////////////////////////////////////////////////////////////////////////////
        if(phase_sq < M_PI)
            sample += amp_sq*1;
        else
            sample += amp_sq*-1;
        
        phase_sq += 2.0*M_PI*invSr*freq_sq;
        

////////////////////////////////////////////////////////////////////////////////
//      Write audio
////////////////////////////////////////////////////////////////////////////////
        // write left channel
        audioWrite(context, i, 0, sample);
        // write right channel
        audioWrite(context, i, 1, sample);
    }
}


void cleanup(BelaContext *context, void *userData)
{

}
