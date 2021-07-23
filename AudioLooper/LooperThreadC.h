#pragma once
#include <SFML/System.hpp>
#include "LooperC.h"
#include "RecorderC.h"

class LooperThreadC 
{
public:
	LooperThreadC() :
		m_thread(&LooperThreadC::Run, this)
	{

	}

	void setLooper(LooperC* looper) 
	{ 
		if (m_looper == nullptr)
		{
			m_looper = new LooperC[sizeof(LooperC)];
		}
		m_looper = looper;
	}
	LooperC* getLooper() { return m_looper; }

	void setSoundBuffer(sf::SoundBuffer* soundBuffer) 
	{ 
		if (!m_soundBuffer)
			m_soundBuffer = new sf::SoundBuffer[sizeof(sf::SoundBuffer)];
		m_soundBuffer = soundBuffer; 
	}
	sf::SoundBuffer* getSoundBuffer() { return m_soundBuffer;  }

	void setLooperState(APPLICATION_FUNCTIONS looperState) { m_looperState = looperState;  }
	APPLICATION_FUNCTIONS getLooperState() { return m_looperState; }

private:
	LooperC* m_looper;
	RecorderC m_recorder;
	sf::SoundBuffer* m_soundBuffer;
	sf::Thread m_thread;

	// Virtual function we override that handles everything the Looper thread needs to do.  
	void Run() {
		switch (m_looperState)
		{
		case APPLICATION_FUNCTIONS::PLAY:
			m_looper->playTrack();
			break;
		case APPLICATION_FUNCTIONS::STOP:
			m_looper->stopTrack();
			break;
		case APPLICATION_FUNCTIONS::RECORD:
			break;
		case APPLICATION_FUNCTIONS::PAUSE:
			m_looper->pauseTrack();
			break;
		default:
			break;
		};
	};

	APPLICATION_FUNCTIONS m_looperState;

};

