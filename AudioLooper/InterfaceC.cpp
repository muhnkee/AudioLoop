#include <SFML/Graphics.hpp>
#include "InterfaceC.h"
#include <iostream>

InterfaceC::InterfaceC() {
	trackCount = 4;
	background_texture.loadFromFile(BACKGROUND);
	background_sprite.setTexture(background_texture);

	// Debug item - this should be loaded at some point
	m_audioFile[0] = "melody.wav";

	if (!font.loadFromFile(ARIAL_FONT))
	{
		// TODO: handle error
	}

	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; i++)
	{
		m_PitchSlider[i] = new Slider[sizeof(Slider)];
		m_PanSlider[i] = new Slider[sizeof(Slider)];
		m_VolumeSlider[i] = new Slider[sizeof(Slider)];

		//Loading slider sprite
		m_PitchSlider[i]->setName("Pitch");
		m_PitchSlider[i]->setSizeScale(.20);

		m_VolumeSlider[i]->setName("Volume");
		m_VolumeSlider[i]->setSizeScale(.20);

		m_PanSlider[i]->setName("Pan");
		m_PanSlider[i]->setSizeScale(.40);
		
		m_PitchSlider[i]->setInitialPosition(SCREEN_WIDTH / 8 + (150 *i), SCREEN_HEIGHT / 8); //relative positioning
		m_VolumeSlider[i]->setInitialPosition(SCREEN_WIDTH / 8 + (150 * i), SCREEN_HEIGHT / 8 + 200);
		m_PanSlider[i]->setInitialPosition(SCREEN_WIDTH / 8 + (200 * i), SCREEN_HEIGHT / 8 + 400);
		trackItem.push_back(sf::Text());

		float barWidth = SCREEN_WIDTH * (1. / 3.);
		float barHeight = SCREEN_HEIGHT / 20.;

		openLooper[i] = false;
	}

	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; ++i)
	{
		slider_container.push_back(m_PitchSlider[i]); //CODE SMELL: accessing sliders from container
	}

	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; ++i)
	{
		slider_container.push_back(m_VolumeSlider[i]);
	}

	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; ++i)
	{
		slider_container.push_back(m_PanSlider[i]);
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


	testLooper.setPitchSlider(slider_container[0]);

  testLooper.shiftPitch(); //start off the pitch where the slider is at
	testLooper.setVolumeSlider(slider_container[1]);
	testLooper.shiftVolume(); //start off the pitch where the slider is at

  //Music seek sprite
	testMusicSeek.setSizeScale(.60);
	testMusicSeek.setInitialPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);
	testMusicSeek.setMusicTrack(testLooper.getMusic());

  testLooper.setPanSlider(slider_container[2]);
}

InterfaceC::~InterfaceC()
{
	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; i++)
	{
		delete[] m_PanSlider[i];
		delete[] m_PitchSlider[i];
		delete[] m_VolumeSlider[i];
	}
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
		slider_container[i]->draw(window);
	}

	testMusicSeek.draw(window);
}	

sf::RenderWindow* InterfaceC::getWindow() {
	return &window;
}

APPLICATION_FUNCTIONS InterfaceC::handleEvent(sf::Event event, int *iLooper)
{
	APPLICATION_FUNCTIONS* retVal;
	retVal = new APPLICATION_FUNCTIONS[sizeof(APPLICATION_FUNCTIONS)];
	*retVal = APPLICATION_FUNCTIONS::NO_CHANGE;

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
	// I started with allocating sliders for channels, but instead we 
	// should do them for function
	// Sliders 0-3 are for Pitch
	// Sliders 4-7 are for Volume
	// Sliders 8-11 are for Pan
	// This allows for expansion based upon function, which is more likely
	// than expansion based upon channel.
	for (int i = 0; i < slider_container.size(); i++)
	{
		sf::Sprite* slider_sprite = slider_container[i]->getSliderSprite();

		// if mouse is on bounds of testSlider
		if (slider_sprite->getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
			&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			slider_container[i]->followMouse();

			// Figure out which slider they're playing with for the controller
			if (slider_container[i]->getName() == "Pitch")
			{
				*functionType = APPLICATION_FUNCTIONS::SET_PITCH;
			}
			else if (slider_container[i]->getName() == "Volume")
			{
				*functionType = APPLICATION_FUNCTIONS::SET_VOLUME;
			}
			else if (slider_container[i]->getName() == "Pan")
			{
				*functionType = APPLICATION_FUNCTIONS::SET_PAN;
			}
			switch (i)
			{
			case 0:
			case 4:
			case 8:
			case 12:
				*iLooper = 0;
				break;
			case 1:
			case 5:
			case 9:
			case 13:
				*iLooper = 1;
				break;
			case 2:
			case 6:
			case 10:
			case 14:
				*iLooper = 2;
				break;
			case 3:
			case 7:
			case 11:
			case 15:
				*iLooper = 3;
				break;
			default:
				*iLooper = 0;
				break;
			}
			break;
		}
	}
	
}

void InterfaceC::handleMouseReleaseEvent() 
{
	for (int i = 0; i < slider_container.size(); i++)
	{
		if (slider_container[i]->isSelected())
		{
			slider_container[i]->stopFollowingMouse();

			// CODE SMELL: not a very good way to handle this, will need to be refactored once core functionality of Looper
			// is built out
			if (slider_container[i]->getName() == "Pitch")
			{
				testLooper.shiftPitch();
			}
			else if (slider_container[i]->getName() == "Volume")
			{
				testLooper.shiftVolume();;
			}
			else if (slider_container[i]->getName() == "Pan")
			{
				testLooper.shiftPan();
			}
		}
		
	}
	
}