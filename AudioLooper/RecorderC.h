#ifndef RECORDER_HPP
#define RECORDER_HPP

extern int DEVICE;

class RecorderC
{
private:

	std::string audioFilePath;
	bool deviceFlag = false;
	sf::SoundBufferRecorder recorder;
	sf::SoundBuffer buffer;
	sf::Sound sound;

public:

	RecorderC();
	void checkAvailabilty();
	void selectDevice();
	void createSamplesDir();
	bool dirExists(const std::string& dirName_in);

	void Record();
	void Stop();
	void Play();

	std::string getAudioFilePath();
};
#endif