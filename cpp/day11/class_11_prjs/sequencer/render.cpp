#include <Bela.h>
#include "Sampler.h"

Sampler kick;
Sampler snare;

float eigths_duration; // in samples
int sampleCnt; // to keep track of samples and recognize eigth notes

float BPM = 95; // beats per minute

// our beat
bool kickbeat[] =  {true, false, false, false, true, false, false, false };
bool snarebeat[] = {false, false, true, false, false, false, true, false };
	
// playhead			   


bool setup(BelaContext *context, void *userData)
{
	if( kick.readFile("kick_02D.WAV", 0, context->audioSampleRate) < 0 )
		return false;
	kick.setLoop(false);	
		
	if( snare.readFile("snare_gate.wav", 0, context->audioSampleRate) < 0 )
		return false;
	snare.setLoop(false);

	float BPS = BPM / 60;
	eigths_duration = 1/(2*BPS)*context->audioSampleRate;
	rt_printf("eigths duration: %f", eigths_duration);
	sampleCnt = eigths_duration - 1;
	
	return true ;
}

int beat_in_measure = 0;
void render(BelaContext *context, void *userData)
{
	float sample;
	for(int n=0; n<context->audioFrames; n++) 
	{
		// check if this sample is an eigth note
		if(++sampleCnt >= eigths_duration) 
		{
			beat_in_measure = (beat_in_measure + 1) % 8;
			if(kickbeat[beat_in_measure])
				kick.play(true);
			if(snarebeat[beat_in_measure])
				snare.play(true);
			
			// reset the counter
			sampleCnt = 0;
		}
		
		// always retrieve samples from sampler
		sample = kick.process()+snare.process(); // when off, they will return 0 
		
		audioWrite(context, n, 0, sample);
		audioWrite(context, n, 1, sample);
	}
}

void cleanup(BelaContext *context, void *userData)
{

}