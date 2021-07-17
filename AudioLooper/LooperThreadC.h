#pragma once
#include <SFML/System.hpp>
#include "LooperC.h"
class LooperThreadC : public sf::Thread
{
public:
	void setLooper(LooperC* looper) { m_looper = looper; }
	LooperC* getLooper() { return m_looper; }

	void setSoundBuffer(sf::SoundBuffer* soundBuffer) { m_soundBuffer = soundBuffer; }
	sf::SoundBuffer* getSoundBuffer() { return m_soundBuffer;  }

	void setLooperState(APPLICATION_FUNCTIONS looperState) { m_looperState = looperState;  }
	APPLICATION_FUNCTIONS getLooperState() { return m_looperState; }

	// Virtual function we override that handles everything the Looper thread needs to do.  
	void Run() { 
		switch (m_looperState)
		{
		case APPLICATION_FUNCTIONS::PLAY:
			break;
		case APPLICATION_FUNCTIONS::STOP:
			break;

		default:
			break;
		};
	};

private:
	LooperC* m_looper;
	sf::SoundBuffer* m_soundBuffer;

	APPLICATION_FUNCTIONS m_looperState;

};

