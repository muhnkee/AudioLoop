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

	void setAudioFileName(int iLooper) { setAudioFile(iLooper); }

	void setThreadNumber(int iThread) { m_iThreadNumber = iThread; }

private:
	RecorderC* m_recorder;
	sf::SoundBuffer* m_soundBuffer;
	sf::Thread m_thread;
	APPLICATION_FUNCTIONS m_looperState;
	int m_iThreadNumber;

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
			if (!(m_recorder->isRecording())) {
				if (isPlaying)
				{
					pauseTrack();
				}
				else
				{
					setTrack(getAudioFile());
					playTrack();
				}
			}
			break;
		case APPLICATION_FUNCTIONS::STOP:
			if (m_recorder->isRecording())
			{
				m_recorder->Stop();
			}
			else if (isPlaying())
			{
				stopTrack();
			}
			break;
		case APPLICATION_FUNCTIONS::RECORD_TO_FILE:
			if (getAudioFile() == "NONE") {
				setAudioFileName(m_iThreadNumber);
				m_recorder->setAudioFilePath(getAudioFile());
			}
			m_recorder->Record(getAudioFile());
			break;
		case APPLICATION_FUNCTIONS::PAUSE:
			if (isPlaying())
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
		m_looperState = APPLICATION_FUNCTIONS::NO_CHANGE;
	};
};

