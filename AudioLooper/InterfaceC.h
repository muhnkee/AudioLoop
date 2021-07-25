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

	//DEBUG: variables used for testing audio
	std::string audioFile = "melody.wav";
	LooperC testLooper;
	Slider testSliderPitch;
	Slider testSliderVolume;
	Slider testSliderPan = Slider(1, 1, true); //landscape slider
	std::vector<Slider> slider_container;
};


