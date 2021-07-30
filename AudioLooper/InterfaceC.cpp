#include <SFML/Graphics.hpp>
#include "InterfaceC.h"
#include <iostream>

InterfaceC::InterfaceC() {
	trackCount = 4;
	background_texture.loadFromFile(BACKGROUND);
	background_sprite.setTexture(background_texture);

	m_PitchSlider  = new Slider[sizeof(Slider)];
	m_PanSlider    = new Slider[sizeof(Slider)];
	m_VolumeSlider = new Slider[sizeof(Slider)];

	if (!font.loadFromFile(ARIAL_FONT))
	{
		// TODO: handle error
	}

	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; i++)
	{
		trackItem.push_back(sf::Text());

		float barWidth = SCREEN_WIDTH * (1. / 3.);
		float barHeight = SCREEN_HEIGHT / 20.;

		openLooper[i] = false;

	}

	//DEBUG
	trackItem[0].setFont(font);
	trackItem[0].setFillColor(sf::Color::Red);
	trackItem[0].setString("play track 1");
	trackItem[0].setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * 1));

	trackItem[1].setFont(font);
	trackItem[1].setFillColor(sf::Color::White);
	trackItem[1].setString("play track 2");
	trackItem[1].setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * 2));

	trackItem[2].setFont(font);
	trackItem[2].setFillColor(sf::Color::White);
	trackItem[2].setString("play track 3");
	trackItem[2].setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * 3));

	trackItem[3].setFont(font);
	trackItem[3].setFillColor(sf::Color::White);
	trackItem[3].setString("play track 4");
	trackItem[3].setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * 4));

	selectedTrackIndex = 0;

	testLooper.setTrack("orchestra-mono.wav"); //this is a MONO track == SFML will play well
	//testLooper.setTrack("melody.wav"); // this is a STEREO track == NO BUENO
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "AudioLoop");

	//Loading slider sprite
	m_PitchSlider->setName("Pitch");
	m_PitchSlider->setSizeScale(.20);

	m_VolumeSlider->setName("Volume");
	m_VolumeSlider->setSizeScale(.20);

	m_PanSlider->setName("Pan");
	m_PanSlider->setSizeScale(.40);

	m_PitchSlider->setInitialPosition(SCREEN_WIDTH/ 8, SCREEN_HEIGHT/8); //relative positioning
	m_VolumeSlider->setInitialPosition(SCREEN_WIDTH / 8 + 100, SCREEN_HEIGHT / 8);
	m_PanSlider->setInitialPosition(SCREEN_WIDTH / 8 + 200, SCREEN_HEIGHT / 8);

	slider_container.push_back(*m_PitchSlider); //CODE SMELL: accessing sliders from container
	slider_container.push_back(*m_VolumeSlider);
	slider_container.push_back(*m_PanSlider);


	testLooper.setPitchSlider(&slider_container[0]);
	testLooper.shiftPitch(); //start off the pitch where the slider is at
	testLooper.setVolumeSlider(&slider_container[1]);
	testLooper.shiftVolume(); //start off the pitch where the slider is at
	testLooper.setPanSlider(&slider_container[2]);
}

InterfaceC::~InterfaceC()
{
	delete[] m_PanSlider;
	delete[] m_PitchSlider;
	delete[] m_VolumeSlider;
}

void InterfaceC::selectNextTrack()
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

void InterfaceC::selectPrevTrack()
{
	trackItem[selectedTrackIndex].setFillColor(sf::Color::White);

	selectedTrackIndex--;
	if (selectedTrackIndex < 0)
	{
		selectedTrackIndex = trackCount - 1;
	}

	trackItem[selectedTrackIndex].setFillColor(sf::Color::Red);
}

void InterfaceC::selectTrackItem(const sf::Event& keyPress, APPLICATION_FUNCTIONS* userSelection, int* iLooper)
{

	switch (keyPress.key.code)
	{
	case sf::Keyboard::Up:
		selectPrevTrack();
		break;
	case sf::Keyboard::Down:
		selectNextTrack();
		break;
	case sf::Keyboard::Enter:
		/*if (openLooper[])
		{
			openLooper[] = false;
		}
		else
		{
			openLooper[] = true;
			}
		*/
		playPauseTrack(testLooper);
		*userSelection = APPLICATION_FUNCTIONS::PLAY;
		break;
	case sf::Keyboard::L:
		loopUnloopTrack(testLooper);
		break;
	case sf::Keyboard::S:
		stopTrack(testLooper);
		*userSelection = APPLICATION_FUNCTIONS::STOP;
		break;
	case sf::Keyboard::P:
		testLooper.shiftPan();
		break;
	case sf::Keyboard::W:
		*userSelection = APPLICATION_FUNCTIONS::SET_TRACK;
		testLooper.setTrack("orchestra-mono.wav");
		break;
	case sf::Keyboard::E:
		*userSelection = APPLICATION_FUNCTIONS::PLAY;
		break;
	default:
		break;
	}

}

void InterfaceC::playPauseTrack(LooperC& looperIn) {
	if (looperIn.isPlaying())
	{
		looperIn.pauseTrack();
	}
	else
	{
		looperIn.playTrack();
	}
}

void InterfaceC::stopTrack(LooperC& looperIn)
{
	looperIn.stopTrack();
}

void InterfaceC::loopUnloopTrack(LooperC& looperIn) {
	if (looperIn.isLooping())
	{
		looperIn.loopTrack(false);
	}
	else
	{
		looperIn.loopTrack(true);
	}
}

void InterfaceC::draw(sf::RenderWindow& window)
{
	window.draw(background_sprite);
	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; i++)
	{
		window.draw(trackItem[i]);
	}

	for (int i = 0; i < slider_container.size(); i++)
	{
		slider_container[i].draw(window);
	}

}

sf::RenderWindow* InterfaceC::getWindow() {
	return &window;
}

APPLICATION_FUNCTIONS InterfaceC::handleEvent(sf::Event event, int *iLooper)
{
	APPLICATION_FUNCTIONS* retVal;
	retVal = new APPLICATION_FUNCTIONS[sizeof(APPLICATION_FUNCTIONS)];

	switch (event.type)
	{
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::KeyReleased:
		selectTrackItem(event, retVal, iLooper); //simplified for now
		break;
	case sf::Event::MouseButtonPressed:
		handleMouseClickEvent(retVal, iLooper);
		break;
	case sf::Event::MouseButtonReleased:
		handleMouseReleaseEvent();
		break;
	default:
		break;
	}

	return(*retVal);
}

void InterfaceC::handleMouseClickEvent(APPLICATION_FUNCTIONS* functionType, int* iLooper)
{
	for (int i = 0; i < slider_container.size(); i++)
	{
		sf::Sprite* slider_sprite = slider_container[i].getSliderSprite();

		// if mouse is on bounds of testSlider
		if (slider_sprite->getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
			&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			slider_container[i].followMouse();

			// Figure out which slider they're playing with for the controller
			if (slider_container[i].getName() == "Pitch")
			{
				*functionType = APPLICATION_FUNCTIONS::SET_PITCH;
			}
			else if (slider_container[i].getName() == "Volume")
			{
				*functionType = APPLICATION_FUNCTIONS::SET_VOLUME;
			}
			else if (slider_container[i].getName() == "Pan")
			{
				*functionType = APPLICATION_FUNCTIONS::SET_PAN;
			}
			break;
		}
	}
	
}

void InterfaceC::handleMouseReleaseEvent() 
{
	for (int i = 0; i < slider_container.size(); i++)
	{
		if (slider_container[i].isSelected())
		{
			slider_container[i].stopFollowingMouse();

			// CODE SMELL: not a very good way to handle this, will need to be refactored once core functionality of Looper
			// is built out
			if (slider_container[i].getName() == "Pitch")
			{
				testLooper.shiftPitch();
			}
			else if (slider_container[i].getName() == "Volume")
			{
				testLooper.shiftVolume();;
			}
			else if (slider_container[i].getName() == "Pan")
			{
				testLooper.shiftPan();
			}
		}
		
	}
	
}