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
		m_MusicSeek[i] = new MusicSeek[sizeof(MusicSeek)];
		m_RecordButton[i] = new ButtonC[sizeof(ButtonC)];
		m_PlayPauseButton[i] = new ButtonC[sizeof(ButtonC)];
		m_StopButton[i] = new ButtonC[sizeof(ButtonC)];
		m_LoopButton[i] = new ButtonC[sizeof(ButtonC)];
		m_ReverseButton[i] = new ButtonC[sizeof(ButtonC)];

		//Loading slider sprite
		m_PitchSlider[i]->setName("Pitch");
		m_PitchSlider[i]->setSizeScale(.20);
		m_PitchSlider[i]->setOrientation();

		m_VolumeSlider[i]->setName("Volume");
		m_VolumeSlider[i]->setSizeScale(.20);
		m_VolumeSlider[i]->setOrientation();

		m_PanSlider[i]->setName("Pan");
		m_PanSlider[i]->setSizeScale(.30);
		m_PanSlider[i]->setOrientation(true); //horizontal
		
		m_PitchSlider[i]->setInitialPosition(SCREEN_WIDTH / 1.5 + (200), SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * (i + 1)-55); //relative positioning
		m_VolumeSlider[i]->setInitialPosition(SCREEN_WIDTH / 1.5 + (300), SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * (i + 1)-55);
		m_PanSlider[i]->setInitialPosition(SCREEN_WIDTH / 2 + 170 - 20, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * (i + 1) + 70);
		trackItem.push_back(sf::Text());

		//Loading MusicSeek sprites
		m_MusicSeek[i]->setSizeScale(.60);
		m_MusicSeek[i]->setInitialPosition(SCREEN_WIDTH / 20, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * (i + 1) - 20);
		
		//Loading ButtonC sprites
		m_RecordButton[i]->setName("Record");
		m_RecordButton[i]->setTexture(RECORD_ICON);
		m_RecordButton[i]->setSizeScale(1.0);
		m_RecordButton[i]->setButtonPosition(SCREEN_WIDTH / 2 + 170 - 40, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * (i + 1));
		
		m_PlayPauseButton[i]->setName("PlayPause");
		m_PlayPauseButton[i]->setTexture(PLAY_PAUSE_ICON);
		m_PlayPauseButton[i]->setSizeScale(.9);
		m_PlayPauseButton[i]->setButtonPosition(SCREEN_WIDTH / 2 + 240 - 40, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * (i + 1));

		m_StopButton[i]->setName("Stop");
		m_StopButton[i]->setTexture(STOP_ICON);
		m_StopButton[i]->setSizeScale(1.1);
		m_StopButton[i]->setButtonPosition(SCREEN_WIDTH / 2 + 310 - 40, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * (i + 1));

		m_LoopButton[i]->setName("Loop");
		m_LoopButton[i]->setTexture(LOOP_ICON);
		m_LoopButton[i]->setSizeScale(1.0);
		m_LoopButton[i]->setButtonPosition(SCREEN_WIDTH / 2 + 380 - 40, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * (i + 1));

		m_ReverseButton[i]->setName("Reverse");
		m_ReverseButton[i]->setTexture(REVERSE_ICON);
		m_ReverseButton[i]->setSizeScale(.9);
		m_ReverseButton[i]->setButtonPosition(SCREEN_WIDTH / 2 + 450 - 40, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * (i + 1));

		float barWidth = SCREEN_WIDTH * (1. / 3.);
		float barHeight = SCREEN_HEIGHT / 20.;

		openLooper[i] = false;
	}

	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; ++i)
	{
		slider_container.push_back(m_PitchSlider[i]);
	}

	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; ++i)
	{
		slider_container.push_back(m_VolumeSlider[i]);
	}

	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; ++i)
	{
		slider_container.push_back(m_PanSlider[i]);
	}

	// packing away the MusicSeek's
	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; ++i)
	{
		seek_container.push_back(m_MusicSeek[i]);
	}

	/*******************************************************/
	// Packing away the buttons
	// Will, I'm going to follow the same convention with the ordering of the buttons <------------
	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; ++i)
	{
		button_container.push_back(m_RecordButton[i]);
	}
	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; ++i)
	{
		button_container.push_back(m_PlayPauseButton[i]);
	}
	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; ++i)
	{
		button_container.push_back(m_StopButton[i]);
	}
	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; ++i)
	{
		button_container.push_back(m_LoopButton[i]);
	}
	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; ++i)
	{
		button_container.push_back(m_ReverseButton[i]);
	}
	/*******************************************************/

	trackItem[0].setFont(font);
	trackItem[0].setFillColor(sf::Color::Red);
	trackItem[0].setString("Track 1");
	trackItem[0].setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * 1));

	trackItem[1].setFont(font);
	trackItem[1].setFillColor(sf::Color::Red);
	trackItem[1].setString("Track 2");
	trackItem[1].setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * 2));

	trackItem[2].setFont(font);
	trackItem[2].setFillColor(sf::Color::Red);
	trackItem[2].setString("Track 3");
	trackItem[2].setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * 3));

	trackItem[3].setFont(font);
	trackItem[3].setFillColor(sf::Color::Red);
	trackItem[3].setString("Track 4");
	trackItem[3].setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / (MAX_NUMBER_OF_TRACKS + 1) * 4));

	selectedTrackIndex = 0;

	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "AudioLoop");
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
		//playPauseTrack(testLooper); //depreciated
		*userSelection = APPLICATION_FUNCTIONS::PLAY;
		break;
	case sf::Keyboard::L:
		//loopUnloopTrack(testLooper); //depreciated
		break;
	case sf::Keyboard::S:
		//stopTrack(testLooper); //depreciated
		*userSelection = APPLICATION_FUNCTIONS::STOP;
		break;
	case sf::Keyboard::P:
		//testLooper.shiftPan(); //depreciated
		break;
	case sf::Keyboard::W:
		*userSelection = APPLICATION_FUNCTIONS::SET_TRACK;
		//testLooper.setTrack("orchestra-mono.wav"); //depreciated
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
	for (int i = 0; i < button_container.size(); i++)
	{
		button_container[i]->draw(window);
	}
	for (int i = 0; i < seek_container.size(); i++)
	{
		seek_container[i]->draw(window);
	}
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
	int iLoops = 0;
	if (slider_container.size() > button_container.size())
	{
		iLoops = slider_container.size();
	}
	else
	{
		iLoops = button_container.size();
	}

	for (int i = 0; i < iLoops; i++)
	{
		if (i < slider_container.size())
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
		if (i < button_container.size())
		{
			sf::Sprite* button_sprite = button_container[i]->getButtonSprite();
			//Will, again I'm follow your lead <----------------------
			if (button_sprite->getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
				&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				// Figure out which slider they're playing with for the controller
				if (button_container[i]->getName() == "Record")
				{
					*functionType = APPLICATION_FUNCTIONS::RECORD_TO_FILE;
				}
				else if (button_container[i]->getName() == "PlayPause")
				{
					if (button_container[i]->isActive())
					{
						*functionType = APPLICATION_FUNCTIONS::PAUSE;
						button_container[i]->setActive(false);
					}
					else
					{
						*functionType = APPLICATION_FUNCTIONS::PLAY;
						button_container[i]->setActive(true);
					}
				}
				else if (button_container[i]->getName() == "Stop")
				{
					*functionType = APPLICATION_FUNCTIONS::STOP;
				}
				else if (button_container[i]->getName() == "Loop")
				{
					*functionType = APPLICATION_FUNCTIONS::LOOP;
					if (button_container[i]->isActive())
					{
						button_container[i]->setActive(false);
					}
					else
					{
						button_container[i]->setActive(true);
					}
				}
				else if (button_container[i]->getName() == "Reverse")
				{
					*functionType = APPLICATION_FUNCTIONS::REVERSE;
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
}

void InterfaceC::handleMouseReleaseEvent() 
{
	for (int i = 0; i < slider_container.size(); i++)
	{
		if (slider_container[i]->isSelected())
		{
			slider_container[i]->stopFollowingMouse();


			if (slider_container[i]->getName() == "Pitch")
			{
				//testLooper.shiftPitch(); // this looper is depreciated, not sure if this is even needed anymore???
			}
			else if (slider_container[i]->getName() == "Volume")
			{
				//testLooper.shiftVolume();;
			}
			else if (slider_container[i]->getName() == "Pan")
			{
				//testLooper.shiftPan();
			}
		}
		
	}
	
}