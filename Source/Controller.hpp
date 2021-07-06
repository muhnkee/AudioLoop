#pragma once
#include "SFML/Graphics.hpp"


class Controller {
public:
	Controller();
	~Controller();

	void selectTrackItem(sf::Event keyPress);
	void selectNextTrack();
	void selectPrevTrack();
	void drawTrackItems(sf::RenderWindow& window);

private:
	int selectedTrackIndex;
	sf::Font font;
	
	std::vector<sf::Text> trackItem;
	int trackCount;
};


