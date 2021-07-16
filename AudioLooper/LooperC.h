#pragma once
#include <string>
#include <SFML/Audio.hpp>;
#include "Slider.h"

class LooperC
{
private:
	sf::Music audioTrack;

	Slider* pitchSlider;
	Slider* volumeSlider;

public:
	LooperC();
	LooperC(std::string audioFile);
	~LooperC();

	void setTrack(std::string fileName);
	void setPitchSlider(Slider* newPitchSlider);
	void setVolumeSlider(Slider* newVolumeSlider);

	void playTrack();
	void pauseTrack();
	void stopTrack();
	void loopTrack(bool toggle);


	double getCurrentPitch();
	void shiftPitch();
	void changeTempo();
	void reverseTrack();
	void adjustVolume(double level);


	bool isPlaying();
	bool isPaused();
	bool isStopped();
	bool isLooping();
};

