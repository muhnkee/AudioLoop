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