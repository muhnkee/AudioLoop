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

	void setSoundBuffer(sf::SoundBuffer* soundBuffer) 
	{ 
		if (!m_soundBuffer)
			m_soundBuffer = new sf::SoundBuffer[sizeof(sf::SoundBuffer)];
		m_soundBuffer = soundBuffer; 
	}
	sf::SoundBuffer* getSoundBuffer() { return m_soundBuffer;  }

	void setRecorder(RecorderC* recorder)
	{
		m_recorder = recorder;
	}
	RecorderC* getRecorder() { return m_recorder; }

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
	APPLICATION_FUNCTIONS m_looperState;
	APPLICATION_FUNCTIONS m_lastLooperState;

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
			setTrack(getAudioFile());
			break;
		case APPLICATION_FUNCTIONS::PLAY:
			playTrack();
			break;
		case APPLICATION_FUNCTIONS::STOP:
			if (m_lastLooperState == APPLICATION_FUNCTIONS::RECORD_TO_FILE)
			{
				m_recorder->Stop();
			}
			else
			{
				stopTrack();
			}
			break;
		case APPLICATION_FUNCTIONS::RECORD_TO_FILE:
			if (getAudioFile() != "NONE") {
				m_recorder->Record();
			}
			break;
		case APPLICATION_FUNCTIONS::RECORD_FROM_FILE:
			setTrack(getAudioFile());
			break;
		case APPLICATION_FUNCTIONS::PAUSE:
			if (m_lastLooperState == APPLICATION_FUNCTIONS::PLAY)
			{
				pauseTrack();
			}
			break;
		case APPLICATION_FUNCTIONS::NEXT:
			break;
		case APPLICATION_FUNCTIONS::PREVIOUS:
			break;
		default:
			break;
		};
		if (m_looperState != APPLICATION_FUNCTIONS::NO_CHANGE) {
			m_lastLooperState = m_looperState;
		}
		m_looperState = APPLICATION_FUNCTIONS::NO_CHANGE;
	};
};

