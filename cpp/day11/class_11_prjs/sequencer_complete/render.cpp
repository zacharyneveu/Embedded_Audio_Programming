#include <Bela.h>
#include "Sampler.h"

Sampler kick;
Sampler snare;

float eigths_duration; // in samples
int sampleCnt; // to keep track of samples and recognize eigth notes

float BPM = 120; // beats per minute

// our beat
int beat[2][8] = { {1, 0, 0, 0, 1, 0, 0, 0},
				   {0, 0, 1, 0, 0, 0, 1, 0} };
				   
int playhead; // to advance the beat


bool setup(BelaContext *context, void *userData)
{
	if( kick.readFile("kick_02D.WAV", 0, context->audioSampleRate) < 0 )
		return false;
	kick.setLoop(false);	
		
	if( snare.readFile("snare_gate.wav", 0, context->audioSampleRate) < 0 )
		return false;
	snare.setLoop(false);
	
	float beat_rate = BPM/60; // beats (fourth notes) per second
	float beat_duration = 1.0/beat_rate; // duration of fourth notes, in seconds
	beat_duration *= context->audioSampleRate; // in samples -> duration in seconds / duration of single sample

	eigths_duration = beat_duration/2; // duration of eight notes, in samples
	
	sampleCnt = eigths_duration-1; // the first sample will be an eigth note
	playhead  = -1; // this will be incremented at each eigth note
	
	return true ;
}

void render(BelaContext *context, void *userData)
{
	float sample;
	for(int n=0; n<context->audioFrames; n++) 
	{
		// check if this sample is an eigth note
		if(++sampleCnt >= eigths_duration) 
		{
			// advance playhead
			if(++playhead >= 8)
				playhead = 0;
			
			// play samplers if on within the beat
			if(beat[0][playhead] == 1)
				kick.play(true);
			if(beat[1][playhead] == 1)
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