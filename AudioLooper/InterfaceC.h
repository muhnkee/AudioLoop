#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "DEFINITIONS.h"
#include "LooperC.h"
#include "Slider.h"

class InterfaceC {
public:
	InterfaceC();
	~InterfaceC();

	void selectTrackItem(const sf::Event& keyPress, APPLICATION_FUNCTIONS *userSelection);
	void handleMouseClickEvent();
	void handleMouseReleaseEvent();
	void playPauseTrack(LooperC& looperIn);
	void stopTrack(LooperC& looperIn);
	void loopUnloopTrack(LooperC& looperIn);
	void selectNextTrack();
	void selectPrevTrack();

	Slider* getVolumeSlider() { return m_VolumeSlider; };
	Slider* getPitchSlider() { return m_PitchSlider; };

	sf::RenderWindow* getWindow();
	void draw(sf::RenderWindow& window);
	APPLICATION_FUNCTIONS handleEvent(sf::Event event, int *iLooper);

private:
	sf::Font font;
	sf::RenderWindow window;
	std::vector<sf::Text> trackItem;
	int trackCount;

	int selectedTrackIndex;

	bool openLooper[MAX_NUMBER_OF_TRACKS];

	Slider* m_VolumeSlider; 
	Slider* m_PitchSlider;

	//DEBUG: variables used for testing audio
	std::string audioFile = "melody.wav";
	LooperC testLooper;
	Slider testSlider;
};


