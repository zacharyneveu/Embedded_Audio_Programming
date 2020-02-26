/***** Sampler.h *****/
#include <string>

using namespace std;

class Sampler 
{
public:
	Sampler();
	int readFile(string fileName, int channel, float srate);
	float process();
	void setLoop(bool on);
	void play(bool on);
	~Sampler();

private:
	int numOfSamples;
	float *samples;
	int currentSampleIndex;
	bool loop;
	bool isPlaying;
};