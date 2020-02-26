/***** FilePlayer.h *****/
#ifndef FILE_PLAYER_H
#define FILE_PLAYER_H

#include <string>

using namespace std;

class FilePlayer 
{

public:
	FilePlayer();
	int readFile(string fileName, int channel, float sampleRate);
	float process();
	void setLoop(bool on);
	~FilePlayer();

private:
	bool loop;
	int numOfSamples;
	float *samples;
	int currentSampleIndex;
}; // <- don't forget semicolon at the end of class declaration!
#endif