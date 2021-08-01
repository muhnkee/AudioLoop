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
			break;
		case APPLICATION_FUNCTIONS::SET_PITCH:
			shiftPitch();
			break;
		case APPLICATION_FUNCTIONS::SET_VOLUME:
			shiftVolume();
			break;
		case APPLICATION_FUNCTIONS::SET_PAN:
			shiftPan();
			break;
		case APPLICATION_FUNCTIONS::SET_TRACK:
			setTrack(m_audioFile);
			break;
		case APPLICATION_FUNCTIONS::PLAY:
			playTrack();
			break;
		case APPLICATION_FUNCTIONS::STOP:
			stopTrack();
			break;
		case APPLICATION_FUNCTIONS::RECORD_TO_FILE:
			m_recorder->Record();
			break;
		case APPLICATION_FUNCTIONS::RECORD_FROM_FILE:

			break;
		case APPLICATION_FUNCTIONS::PAUSE:
			pauseTrack();
			break;
		case APPLICATION_FUNCTIONS::NEXT:
			break;
		case APPLICATION_FUNCTIONS::PREVIOUS:
			break;
		default:
			break;
		};

		m_looperState = APPLICATION_FUNCTIONS::NO_CHANGE;
	};

	APPLICATION_FUNCTIONS m_looperState;

};

