#include "ButtonC.h"
#include "ControllerC.h"
#include <iostream>

ControllerC::ControllerC() :
m_gui_interface()
{

}

int ControllerC::run()
{
	// Create a window
	sf::RenderWindow* application = m_gui_interface.getWindow();

	application->setMouseCursorVisible(true);
	// a common sound buffer to point everyone to
	sf::SoundBuffer* soundBuffer;
	soundBuffer = new sf::SoundBuffer[sizeof(sf::SoundBuffer)];

	sf::SoundBufferRecorder* soundBufferRecorder;
	soundBufferRecorder = new sf::SoundBufferRecorder[sizeof(sf::SoundBufferRecorder)];

	RecorderC* recorder;
	recorder = new RecorderC(soundBufferRecorder, soundBuffer);

	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; ++i)
	{
		m_Looper[i].setSoundBuffer(soundBuffer);
		// This should point everyone towards the same recorder/buffer.
		m_Looper[i].setRecorder(recorder);
	}
	int* iLooper;
	iLooper = new int[sizeof(int)];
	*iLooper = 0;

	while (application->isOpen())
	{

		for (int i = 0; i < MAX_NUMBER_OF_TRACKS; ++i)
		{
			m_Looper[i].launchThread();
		}
		sf::Event event;

		while (application->pollEvent(event))
		{
			APPLICATION_FUNCTIONS applicationState = APPLICATION_FUNCTIONS::NO_CHANGE;
			applicationState = m_gui_interface.handleEvent(event, iLooper);

			if (applicationState == APPLICATION_FUNCTIONS::SET_VOLUME)
			{
				m_Looper[*iLooper].setVolumeSlider(m_gui_interface.getVolumeSlider(*iLooper));
			}
			else if (applicationState == APPLICATION_FUNCTIONS::SET_PITCH)
			{
				m_Looper[*iLooper].setPitchSlider(m_gui_interface.getPitchSlider(*iLooper));
			}
			else if (applicationState == APPLICATION_FUNCTIONS::SET_PAN)
			{
				m_Looper[*iLooper].setPanSlider(m_gui_interface.getPanSlider(*iLooper));
			}
			else if (applicationState == APPLICATION_FUNCTIONS::SET_TRACK)
			{
				if (m_gui_interface.getAudioFile(*iLooper) != "NONE")
				{
					m_Looper[*iLooper].setAudioFile(m_gui_interface.getAudioFile(*iLooper));
				}
			}
			else if (applicationState == APPLICATION_FUNCTIONS::RECORD_TO_FILE)
			{
				m_Looper[*iLooper].setAudioFileName();
			}

			m_Looper[*iLooper].setLooperState(applicationState);
		}

		application->clear();

		m_gui_interface.draw(*application);
		application->display();

	}

	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; ++i)
	{
		m_Looper[i].terminateThread();
	}

	delete[] iLooper;
	delete[] soundBuffer;
	return 0;
}
