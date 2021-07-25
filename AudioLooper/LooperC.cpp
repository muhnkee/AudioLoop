#pragma once
#include "DEFINITIONS.h"
#include <stdlib.h>
#include <iostream>
#include "LooperC.h"
#include <SFML/Audio.hpp>;
#include <cmath>


LooperC::LooperC()
{

}

LooperC::~LooperC()
{

}

LooperC::LooperC(std::string audioFile)
{
	audioTrack.openFromFile(AUDIO_DIR + audioFile);

	// set spacial audio properties for panning
	audioTrack.setMinDistance(1.f);
	audioTrack.setAttenuation(1.f);
	audioTrack.setRelativeToListener(true);
}

void LooperC::setTrack(std::string fileName)
{
	audioTrack.openFromFile(AUDIO_DIR + fileName);

	// set spacial audio properties for panning
	audioTrack.setMinDistance(1.f);
	audioTrack.setAttenuation(1.f);
	audioTrack.setRelativeToListener(true);
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

/// <summary>
/// Return the current volume level of the track
/// </summary>
/// <returns>double -The level of the volume</returns>
double LooperC::getCurrentVolume() {
	return audioTrack.getVolume();
}

/// <summary>
/// Adjust the volume level of the track
/// </summary>
void LooperC::shiftVolume() {
#ifdef DEBUG
	std::cout << "current volume = " << getCurrentVolume() << std::endl;

#endif // DEBUG
	// this math allows us to have both high and low ranges
	// TODO: the mathing will need some adjustment, right now it gets really quite really quick on the slider movement
	//			but for now its acceptable
	double baseLevel = volumeSlider->getLevel() * 2; // get the volume to 1.0 for a proper exponential base
	double newVolume = std::pow(baseLevel, 10); // exponentialy grow the volume
	
	audioTrack.setVolume(newVolume);
}

/// <summary>
/// Used so we can access audioTrack methods outside of the LooperC class
/// </summary>
/// <returns>sf::Music* - pointer to this audioTrack</returns>
sf::Music* LooperC::getMusic()
{
	return &audioTrack;
}

/// <summary>
/// Ties a slider to this Looper for adjusting its pan
/// </summary>
/// <param name="newPanSlider"> - Reference to an existing gui slider </param>
void LooperC::setPanSlider(Slider* newPanSlider)
{
	panSlider = newPanSlider;
}

/// <summary>
/// adjust the left/right panning of the audio track
/// 
/// Audio Spacialization works on a 2D grid system with the "Listener" (your speakers)
/// in the center (0,0) coordinate of a semicircle. Adjusting the slider left and right
/// has the audioTrack walk the perimiter of the semi circle, so that the audio track comes
/// out of the left and/or right speakers at individual volumes dictated by its position
/// in the semicircle and with respect to the Listener at the center.
/// 
/// 
///		      	      	     Equal
///                          (0,10)  
///                         .  .  .
///                     .   \  |  /   .
///                  .       \ | /      .
///                .          \|/         .
/// ((-10,0)=Left).------------X-----------.((10,0)=Right)
/// </summary>
void LooperC::shiftPan()
{
	// is this needed upon setup of Looper audio buffer?
	

	// for horizontal slider, full left is 0.0, middle is .5, full right is 1.0
	double baseLevel = panSlider->getLevel();

	sf::Vector3f position;
	float radius = 10.f;

	double angle = 180 - (180 * baseLevel);
	double radians = angle * (PI / 180.);
	position.x = radius * std::cos(radians); // the x value
	position.y = 0.f;
	position.z = radius* std::sin(radians); //THIS is the 'Y' value in the grid

	
	// for panning position, full left is -10, center is 0, right is 10
	audioTrack.setPosition(position);
#ifdef DEBUG
	std::cout << "x: " << position.x << " y: " << position.y << " z: " << position.z << std::endl;
	std::cout << "angle: " << angle << std::endl;
#endif // DEBUG
}
