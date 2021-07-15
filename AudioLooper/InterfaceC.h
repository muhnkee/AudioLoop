#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "LooperC.h"
#include "Slider.h"

class InterfaceC {
public:
	InterfaceC();
	~InterfaceC();

	void selectTrackItem(const sf::Event& keyPress);
	void handleMouseClickEvent();
	void handleMouseReleaseEvent();
	void playPauseTrack(LooperC& looperIn);
	void stopTrack(LooperC& looperIn);
	void loopUnloopTrack(LooperC& looperIn);
	void selectNextTrack();
	void selectPrevTrack();


	sf::RenderWindow* getWindow();
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);

private:
	
	sf::Font font;
	sf::RenderWindow window;
	std::vector<sf::Text> trackItem;
	int trackCount;

	int selectedTrackIndex;

	//DEBUG: variables used for testing audio
	std::string audioFile = "melody.wav";
	LooperC testLooper;
	Slider testSlider;
};

