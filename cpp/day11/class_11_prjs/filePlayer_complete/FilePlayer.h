/***** FilePlayer.h *****/
#include <string>

using namespace std;

class FilePlayer 
{
public:
	FilePlayer();
	int readFile(string fileName, int channel, float srate);
	float process();
	void setLoop(bool on);
	void restart();
	~FilePlayer();

private:
	int numOfSamples;
	float *samples;
	int currentSampleIndex;
	bool loop;
};