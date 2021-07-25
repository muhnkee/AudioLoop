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
	Slider* panSlider;

public:
	LooperC();
	LooperC(std::string audioFile);
	~LooperC();

	sf::Music* getMusic();

	void setTrack(std::string fileName);
	void setPitchSlider(Slider* newPitchSlider);
	void setVolumeSlider(Slider* newVolumeSlider);
	void setPanSlider(Slider* newPanSlider);

	void playTrack();
	void pauseTrack();
	void stopTrack();
	void loopTrack(bool toggle);


	double getCurrentPitch();
	void shiftPitch();
	double getCurrentVolume();
	void shiftVolume();
	void shiftPan();

	void changeTempo();
	void reverseTrack();


	bool isPlaying();
	bool isPaused();
	bool isStopped();
	bool isLooping();
};

