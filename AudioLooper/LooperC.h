#pragma once
#include <string>
#include <SFML/Audio.hpp>;

class LooperC
{
private:
	sf::Music audioTrack;

public:
	LooperC();
	LooperC(std::string audioFile);
	~LooperC();

	void setTrack(std::string fileName);

	void playTrack();
	void pauseTrack();
	void stopTrack();
	void loopTrack(bool toggle);
	void shiftPitch();
	void changeTempo();
	void reverseTrack();


	bool isPlaying();
	bool isPaused();
	bool isStopped();
	bool isLooping();
};

