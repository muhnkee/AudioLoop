#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "DEFINITIONS.h"
#include "LooperC.h"
#include "Slider.h"
#include "MusicSeek.h"

class InterfaceC {
public:
	InterfaceC();
	~InterfaceC();

	void selectTrackItem(const sf::Event& keyPress, APPLICATION_FUNCTIONS *userSelection, int* iLooper);

	void handleMouseClickEvent(APPLICATION_FUNCTIONS* retVal, int* iLooper);
	void handleMouseReleaseEvent();
	void playPauseTrack(LooperC& looperIn);
	void stopTrack(LooperC& looperIn);
	void loopUnloopTrack(LooperC& looperIn);
	void selectNextTrack();
	void selectPrevTrack();

	Slider* getVolumeSlider(int iChannel) { return m_VolumeSlider[iChannel]; };
	void setVolumeSlider(Slider* slider, int iChannel) { m_VolumeSlider[iChannel] = slider;  }
	Slider* getPitchSlider(int iChannel) { return m_PitchSlider[iChannel]; };
	void setPitchSlider(Slider* slider, int iChannel) { m_PitchSlider[iChannel] = slider; }
	Slider* getPanSlider (int iChannel) { return m_PanSlider[iChannel]; };
	void setPanSlider(Slider* slider, int iChannel) { m_PanSlider[iChannel] = slider; }

	std::string getAudioFile(int iChannel) { return m_audioFile[iChannel];  }
	void setAudioFile(std::string audioFile, int iChannel) { m_audioFile[iChannel] = audioFile; }

	sf::RenderWindow* getWindow();
	void draw(sf::RenderWindow& window);
	APPLICATION_FUNCTIONS handleEvent(sf::Event event, int* iLooper);

private:
	sf::Font font;
	sf::RenderWindow window;
	std::vector<sf::Text> trackItem;
	sf::Texture background_texture;
	sf::Sprite background_sprite;

	int trackCount;

	int selectedTrackIndex;

	bool openLooper[MAX_NUMBER_OF_TRACKS];
	
	MusicSeek testMusicSeek;
	Slider* m_VolumeSlider[MAX_NUMBER_OF_TRACKS];
	Slider* m_PitchSlider[MAX_NUMBER_OF_TRACKS];
	Slider* m_PanSlider[MAX_NUMBER_OF_TRACKS];
	std::string m_audioFile[MAX_NUMBER_OF_TRACKS];

	//DEBUG: variables used for testing audio
	LooperC testLooper;
	Slider testSliderPitch;
	Slider testSliderVolume;
	//Slider testSliderPan = Slider(true); //landscape slider
	std::vector<Slider*> slider_container;
};


