/*
 * Copyright (C) 2020 zach zachary.neveu@gmail.com
 */

#include <Bela.h>
#include <cmath>
#include <random>
#include <stdlib.h>
#include <libraries/Biquad/Biquad.h>
#include <libraries/Oscillator/Oscillator.h>
#include <libraries/ADSR/ADSR.h>
#include "utils.h"

Oscillator osc_sin;
float freq_sin = 130.81; // osc freq in Hz
float amp = db2amp(12);


ADSR ampEnv;
float ampAttack  = 0; // s
float ampDecay   = 2; // s
float ampSustain = 0; // s
float ampRelease = 0; // s

ADSR freqEnv;
float freqAttack  = 0;
float freqDecay   = 0.08;
float freqSustain = 0.125;
float freqRelease = 1;

Oscillator LFO;
float lfoRate  = 40; // hz - 15 would be better on proper system
float lfoDepth = 0.05;

// Return true if all goes well
bool setup(BelaContext *context, void *userData)
{
    ampEnv.setAttackRate(ampAttack*context->audioSampleRate);
    ampEnv.setDecayRate(ampDecay*context->audioSampleRate);
    ampEnv.setSustainLevel(ampSustain);
    ampEnv.setReleaseRate(ampRelease*context->audioSampleRate);
    ampEnv.gate(true);

    freqEnv.setAttackRate  (freqAttack*context->audioSampleRate);
    freqEnv.setDecayRate   (freqDecay*context->audioSampleRate);
    freqEnv.setSustainLevel(freqSustain);
    freqEnv.setReleaseRate (freqRelease*context->audioSampleRate);
    freqEnv.setTargetRatioDR(0.01); //linear vs. logarithmic
    freqEnv.gate(true);

    LFO.setup(lfoRate, context->audioSampleRate, Oscillator::sine);

	osc_sin.setup(freq_sin, context->audioSampleRate, Oscillator::sine, 0);
	return true;
}

// Triggered by audio interface interrupt
// returns an array of size Block_Size x n_channels
int counter = 0; //whataname.exe
void render(BelaContext *context, void *userData)
{
    if(counter < 1000)
    {
        counter++;
        return;
    }

    float sample, ampSample, freqSample;

    for (int i = 0; i < context->audioFrames; i++)
    {
        freqSample = freqEnv.process();
        osc_sin.setFrequency(freqSample*freq_sin);

		ampSample = ampEnv.process();
        sample = osc_sin.process() * amp * ampSample;
        sample = (1-lfoDepth) * sample + lfoDepth * sample * (LFO.process()+1)/2;

        // write left channel
        audioWrite(context, i, 0, sample);
        // write right channel
        audioWrite(context, i, 1, sample);
    }
}


void cleanup(BelaContext *context, void *userData)
{

}