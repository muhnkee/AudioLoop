#pragma once
#include <SFML/System.hpp>
#include "LooperC.h"
#include "RecorderC.h"

class LooperThreadC: public LooperC
{
public:
	LooperThreadC() :
		m_thread(&LooperThreadC::Run, this)
	{
	}

	//void setVolumeSlider(Slider* slider) { m_VolumeSlider = slider;  }
	//Slider* getVolumeSlider() { return m_VolumeSlider; }

	//void setPitchSlider(Slider* slider) { m_PitchSlider = slider; }
	//Slider* getPitchSlider() { return m_PitchSlider; }

	//void setPanSlider(Slider* slider) { m_PanSlider = slider; }
	//Slider* getPanSlider() { return m_PanSlider; }

	void setAudioFile(std::string audioFile) { m_audioFile = audioFile;  }
	std::string getAudioFile() { return m_audioFile;  }

	void setSoundBuffer(sf::SoundBuffer* soundBuffer) 
	{ 
		if (!m_soundBuffer)
			m_soundBuffer = new sf::SoundBuffer[sizeof(sf::SoundBuffer)];
		m_soundBuffer = soundBuffer; 
	}
	sf::SoundBuffer* getSoundBuffer() { return m_soundBuffer;  }

	void setLooperState(APPLICATION_FUNCTIONS looperState) { 
		m_looperState = looperState;  
	}

	APPLICATION_FUNCTIONS getLooperState() { return m_looperState; }

	void launchThread() { m_thread.launch();  }
	void terminateThread() { m_thread.terminate(); }
	void pauseThread() { m_thread.wait(); }

private:
	RecorderC* m_recorder;
	sf::SoundBuffer* m_soundBuffer;
	sf::Thread m_thread;

	std::string m_audioFile;

	// Virtual function we override that handles everything the Looper thread needs to do.  
	void Run() {
		switch (m_looperState)
		{
		case APPLICATION_FUNCTIONS::LOOP:
			//m_looper->loopTrack();
			break;
		case APPLICATION_FUNCTIONS::SET_PITCH:
			shiftPitch();
			break;
		case APPLICATION_FUNCTIONS::SET_VOLUME:
			shiftVolume();
			break;
		case APPLICATION_FUNCTIONS::SET_PAN:
			shiftPan();
		case APPLICATION_FUNCTIONS::PLAY:
			playTrack();
			break;
		case APPLICATION_FUNCTIONS::STOP:
			stopTrack();
			break;
		case APPLICATION_FUNCTIONS::RECORD_TO_FILE:

			break;
		case APPLICATION_FUNCTIONS::RECORD_FROM_FILE:

			break;
		case APPLICATION_FUNCTIONS::PAUSE:
			pauseTrack();
			break;
		default:
			break;
		};
	};

	APPLICATION_FUNCTIONS m_looperState;

};

