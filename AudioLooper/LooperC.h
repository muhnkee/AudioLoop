#pragma once
#include <string>
#include <SFML/Audio.hpp>;
#include "Slider.h"
#include "Reverse.h"
#include "ButtonC.h"
#include "MusicSeek.h"

using std::to_string;

class LooperC 
{
private:
	sf::Music audioTrack;
	std::string m_audioFile;

	MusicSeek* musicSeekBar;
	Slider* pitchSlider;
	Slider* volumeSlider;
	Slider* panSlider;
	ButtonC* recordButton;
	ButtonC* playPauseButton;
	ButtonC* stopButton;
	ButtonC* loopButton;
	ButtonC* reverseButton;

	bool trackSet;

public:
	LooperC();
	LooperC(std::string audioFile);
	~LooperC();

	sf::Music* getMusic();

	void setTrack(std::string fileName);
	void setPitchSlider(Slider* newPitchSlider);
	void setVolumeSlider(Slider* newVolumeSlider);
	void setPanSlider(Slider* newPanSlider);
	void setMusicSeekBar(MusicSeek* newMusicSeek);
	void setRecordButton(ButtonC* newRecordButton);
	void setPlayPauseButton(ButtonC* newPlayPauseButton);
	void setStopButton(ButtonC* newStopButton);
	void setLoopButton(ButtonC* newLoopButton);
	void setReverseButton(ButtonC* newReverseButton);

	void playTrack();
	void pauseTrack();
	void stopTrack();
	void loopTrack(bool toggle);


	double getCurrentPitch();
	void shiftPitch();
	double getCurrentVolume();
	void shiftVolume();
	void shiftPan();

	void reverseTrack();

	bool isPlaying();
	bool isPaused();
	bool isStopped();
	bool isLooping();
	bool isTrackSet();

	void setAudioFile(int iLooper) { m_audioFile = "Samples/Looper_" + to_string(iLooper) + ".wav"; }
	std::string getAudioFile() {
		if (m_audioFile != "")
			return m_audioFile;
		
		return "NONE";
	}
};

