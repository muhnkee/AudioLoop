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

	void selectTrackItem(const sf::Event& keyPress, APPLICATION_FUNCTIONS *userSelection, int* iLooper);

	void handleMouseClickEvent(APPLICATION_FUNCTIONS* retVal, int* iLooper);
	void handleMouseReleaseEvent();
	void playPauseTrack(LooperC& looperIn);
	void stopTrack(LooperC& looperIn);
	void loopUnloopTrack(LooperC& looperIn);
	void selectNextTrack();
	void selectPrevTrack();

	Slider* getVolumeSlider() { return m_VolumeSlider; };
	void setVolumeSlider(Slider* slider) { m_VolumeSlider = slider;  }
	Slider* getPitchSlider() { return m_PitchSlider; };
	void setPitchSlider(Slider* slider) { m_PitchSlider = slider; }
	Slider* getPanSlider () { return m_PanSlider; };
	void setPanSlider(Slider* slider) { m_PanSlider = slider; }

	std::string getAudioFile() { return m_audioFile;  }
	void setAudioFile(std::string audioFile) { m_audioFile = audioFile; }

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

	Slider* m_VolumeSlider; 
	Slider* m_PitchSlider;
	Slider* m_PanSlider;
	std::string m_audioFile;
	//DEBUG: variables used for testing audio <----- what is depreciated???
	//Slider testSliderPitch;
	//Slider testSliderVolume;
	//Slider testSliderPan = Slider(true); //landscape slider, depreciated 

	LooperC testLooper;
	std::vector<Slider> slider_container;
};


