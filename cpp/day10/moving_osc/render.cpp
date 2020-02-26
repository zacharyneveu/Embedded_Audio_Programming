#include <Bela.h>
#include <cmath>

float freq_sine = 220; // Hz [A3 note]
float amp_sine = 0.2;
float phase_sine;

float freq_square = 49; // Hz [G2 note]
float amp_square = 0.05;
float phase_square;

float freq_lfo = 0.25; // Hz
float phase_lfo;

float invSrate;


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
	phase_lfo = 0;
	
	return true;
}

void render(BelaContext *context, void *userData)
{
	float sample_sine;
	float sample_square;
	float lfo;
	
	float frame[2];

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
		
		
		
		// low frequency oscillator [sine] for panning
		lfo = sinf(phase_lfo);
		phase_lfo = advancePhase(phase_lfo, freq_lfo);
		
		// inverse panning for sine and squarewave
		// lfo < 0 -> sine to right and square to left
		// lfo > 0 -> sine to left and square to right
		
		// lfo < 0 -> sine to right and square to left
		if(lfo < 0) {
			// left channel
			frame[0] = (1+lfo)*sample_sine; // attenuate sine
			frame[0] += sample_square; // add square at max amp

			// right channel
			frame[1] = sample_sine; // sine at max amp
			frame[1] += (1+lfo)*sample_square; // add attenuated square
			
		}
		else // lfo <= 0 -> sine to right and square to left [opposite logic]
		{
			frame[0] = sample_sine; // sine at max amp
			frame[0] += (1-lfo)*sample_square; // add attenuated square

			frame[1] = (1-lfo)*sample_sine; // attenuate sine
			frame[1] += sample_square; // add square at max amp
		}
		
		
		
		audioWrite(context, n, 0, frame[0]);
		audioWrite(context, n, 1, frame[1]);
	}
}

void cleanup(BelaContext *context, void *userData)
{

}