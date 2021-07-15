#pragma once
#include "DEFINITIONS.h"
#include <stdlib.h>
#include <iostream>
#include "LooperC.h"
#include <SFML/Audio.hpp>;


LooperC::LooperC()
{

}

LooperC::~LooperC()
{

}

LooperC::LooperC(std::string audioFile)
{
	audioTrack.openFromFile(AUDIO_DIR + audioFile);
}

void LooperC::setTrack(std::string fileName)
{
	audioTrack.openFromFile(AUDIO_DIR + fileName);
}

// track manipulation
void LooperC::playTrack() {
	audioTrack.play();
}
void LooperC::pauseTrack() {
	audioTrack.pause();
}
void LooperC::stopTrack() {
	audioTrack.stop();
}
void LooperC::loopTrack(bool toggle) {
	audioTrack.setLoop(toggle);
}

// status checkers
bool LooperC::isPlaying() {
	if (audioTrack.getStatus() == sf::SoundSource::Status::Playing)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool LooperC::isPaused() {
	if (audioTrack.getStatus() == sf::SoundSource::Status::Paused)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool LooperC::isStopped() {
	if (audioTrack.getStatus() == sf::SoundSource::Status::Stopped)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool LooperC::isLooping() {
	return audioTrack.getLoop();
}


/// <summary>
/// Return the current pitch level of the track
/// </summary>
/// <returns>double -The level of the pitch</returns>
double LooperC::getCurrentPitch() {
	return audioTrack.getPitch();
}

/// <summary>
/// Adjust the pitch level of the track
/// </summary>
/// <param name="pitchLevel"> -The new pitch level</param>
void LooperC::shiftPitch() {
#ifdef DEBUG
	std::cout << "current pitch = " << getCurrentPitch() << std::endl;

#endif // DEBUG
	//multiply by 2 b/c normal pitch is at 1.0 and slider starts at .5
	// this allows us to have both high and low ranges
	audioTrack.setPitch(pitchSlider->getLevel() *2); 
}

/// <summary>
/// Ties a slider to this Looper for adjusting its pitch
/// </summary>
/// <param name="newPitchSlider"> -Reference to an existing gui slider</param>
void LooperC::setPitchSlider(Slider* newPitchSlider) {
	pitchSlider = newPitchSlider;
	audioTrack.setPitch(pitchSlider->getLevel() * 2);
}

/// <summary>
/// Ties a slider to this Looper for adjusting its volume
/// </summary>
/// <param name="newVolumeSlider">-Reference to an existing gui slider</param>
void LooperC::setVolumeSlider(Slider* newVolumeSlider) {
	volumeSlider = newVolumeSlider;
}
