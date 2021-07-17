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

	// Virtual function we override that handles everything the Looper thread needs to do.  
	void Run() { ; };

private:
	LooperC* m_looper;
	sf::SoundBuffer* m_soundBuffer;

};

