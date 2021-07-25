#include <SFML/Graphics.hpp>
#include "InterfaceC.h"
#include <iostream>

InterfaceC::InterfaceC() {
	trackCount = 4;

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
	testSliderPitch.setName("pitch"); 
	testSliderPitch.setSizeScale(.20);

	testSliderVolume.setName("volume");
	testSliderVolume.setSizeScale(.20);

	testSliderPan.setName("pan");
	testSliderPan.setSizeScale(.40);

	testSliderPitch.setInitialPosition(SCREEN_WIDTH/ 8, SCREEN_HEIGHT/8); //relative positioning
	testSliderVolume.setInitialPosition(SCREEN_WIDTH / 8 + 100, SCREEN_HEIGHT / 8);
	testSliderPan.setInitialPosition(SCREEN_WIDTH / 8 + 200, SCREEN_HEIGHT / 8);

	slider_container.push_back(testSliderPitch); //CODE SMELL: accessing sliders from container
	slider_container.push_back(testSliderVolume);
	slider_container.push_back(testSliderPan);

	testLooper.setPitchSlider(&slider_container[0]);
	testLooper.shiftPitch(); //start off the pitch where the slider is at
	testLooper.setVolumeSlider(&slider_container[1]);
	testLooper.shiftVolume(); //start off the pitch where the slider is at
	testLooper.setPanSlider(&slider_container[2]);
}

InterfaceC::~InterfaceC()
{
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

void InterfaceC::selectTrackItem(const sf::Event& keyPress)
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
		break;
	case sf::Keyboard::L:
		loopUnloopTrack(testLooper);
		break;
	case sf::Keyboard::S:
		stopTrack(testLooper);
		break;
	case sf::Keyboard::P:
		testLooper.shiftPan();
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
	APPLICATION_FUNCTIONS retVal = APPLICATION_FUNCTIONS::NO_CHANGE;

	switch (event.type)
	{
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::KeyReleased:
		selectTrackItem(event); //simplified for now
		break;
	case sf::Event::MouseButtonPressed:
		handleMouseClickEvent();
		break;
	case sf::Event::MouseButtonReleased:
		handleMouseReleaseEvent();
		break;
	default:
		break;
	}

	return(retVal);
}

void InterfaceC::handleMouseClickEvent()
{
	for (int i = 0; i < slider_container.size(); i++)
	{
		sf::Sprite* slider_sprite = slider_container[i].getSliderSprite();

		// if mouse is on bounds of testSlider
		if (slider_sprite->getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
			&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			slider_container[i].followMouse();


			// CODE SMELL: not a very good way to handle this, will need to be refactored once core functionality of Looper
			// is built out
			if (slider_container[i].getName() == "pitch")
			{
				testLooper.shiftPitch();
			}
			else if (slider_container[i].getName() == "volume")
			{
				testLooper.shiftVolume();
			}
			else if (slider_container[i].getName() == "pan")
			{
				testLooper.shiftPan();
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
			if (slider_container[i].getName() == "pitch")
			{
				testLooper.shiftPitch();
			}
			else if (slider_container[i].getName() == "volume")
			{
				testLooper.shiftVolume();;
			}
			else if (slider_container[i].getName() == "pan")
			{
				testLooper.shiftPan();
			}
		}
		
	}
	
}