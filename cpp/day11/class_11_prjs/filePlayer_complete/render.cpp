#include <Bela.h>
#include "FilePlayer.h"

FilePlayer player;

bool setup(BelaContext *context, void *userData)
{
	if( player.readFile("waves.wav", 0, context->audioSampleRate) < 0 )
		return false;
	
	player.setLoop(false);	
		
	return true;
}

//int cnt = 0;
void render(BelaContext *context, void *userData)
{
	float sample;
	for(int n=0; n<context->audioFrames; n++) 
	{
		/*if(++cnt > 4410)
		{
			cnt = 0;
			player.restart();
		}*/
		
		sample = player.process();
		audioWrite(context, n, 0, sample);
		audioWrite(context, n, 1, sample);
	}
}

void cleanup(BelaContext *context, void *userData)
{

}