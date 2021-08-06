#ifndef RECORDER_HPP
#define RECORDER_HPP

extern int DEVICE;

class RecorderC
{
private:

	std::string audioFilePath;
	bool deviceFlag = false;
	sf::SoundBufferRecorder* recorder;
	sf::SoundBuffer* buffer;
	sf::Sound sound;

	bool m_isRecording = false;

public:

	RecorderC(sf::SoundBufferRecorder* recorder, sf::SoundBuffer* buffer);

	void setBuffer(sf::SoundBuffer* bufferIn) { buffer = bufferIn; }
	void setRecorderBuffer(sf::SoundBufferRecorder* bufferIn) { recorder = bufferIn;  }

	void setAudioFilePath(std::string newAudioFilePath);

	void checkAvailabilty();
	void selectDevice();
	void createSamplesDir();
	bool dirExists(const std::string& dirName_in);

	void Record(std::string fileName);
	void Stop();
	void Play();
	
	bool isRecording();

	std::string getAudioFilePath();
};
#endif