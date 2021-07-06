#include <SFML/Graphics.hpp>
#include "Controller.hpp"
#include "DEFINITIONS.hpp"


Controller::Controller() {
	trackCount = 3; //DEBUGGING AT 3 FOR NOW, CHANGE TO 0 <---------------

	if (!font.loadFromFile(ARIAL_FONT)) 
	{
		// TODO: handle error
	}

	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; i++)
	{
		trackItem.push_back(sf::Text());
	}

	trackItem[0].setFont(font);
	trackItem[0].setFillColor(sf::Color::Red);
	trackItem[0].setString("play sound 1");
	trackItem[0].setPosition(sf::Vector2f(SCREEN_WIDTH/ 2, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) *1));

	trackItem[1].setFont(font);
	trackItem[1].setFillColor(sf::Color::White);
	trackItem[1].setString("play sound 2");
	trackItem[1].setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * 2));

	trackItem[2].setFont(font);
	trackItem[2].setFillColor(sf::Color::White);
	trackItem[2].setString("play sound 3");
	trackItem[2].setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * 3));


	selectedTrackIndex = 0;
}

Controller::~Controller()
{
}



void Controller::selectNextTrack()
{
	trackItem[selectedTrackIndex].setFillColor(sf::Color::White);

	selectedTrackIndex++;
	if (selectedTrackIndex >= trackCount)
	{
		selectedTrackIndex = 0;
	}

	trackItem[selectedTrackIndex].setFillColor(sf::Color::Red);
	//TODO: create "current selected track" member variable
}

void Controller::selectPrevTrack()
{

	trackItem[selectedTrackIndex].setFillColor(sf::Color::White);

	selectedTrackIndex--;
	if (selectedTrackIndex < 0)
	{
		selectedTrackIndex = trackCount - 1;
	}

	trackItem[selectedTrackIndex].setFillColor(sf::Color::Red);
	//TODO: create "current selected track" member variable
}

void Controller::selectTrackItem(sf::Event keyPress)
{
	switch (keyPress.key.code)
	{
	case sf::Keyboard::Up:
		selectPrevTrack();
		break;
	case sf::Keyboard::Down:
		selectNextTrack();
		break;
	default:
		break;
	}

}

void Controller::drawTrackItems(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; i++)
	{
		window.draw(trackItem[i]);
	}
}