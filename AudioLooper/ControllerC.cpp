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

	for (int i = 0; i < MAX_NUMBER_OF_TRACKS; ++i)
	{
		m_Looper[i].setSoundBuffer(soundBuffer);
	}
	int* iLooper;
	iLooper = new int[sizeof(int)];
	*iLooper = 0;

	while (application->isOpen())
	{
		sf::Event event;

		while (application->pollEvent(event))
		{
			APPLICATION_FUNCTIONS applicationState = APPLICATION_FUNCTIONS::NO_CHANGE;
			applicationState = m_gui_interface.handleEvent(event, iLooper);

			if (applicationState == APPLICATION_FUNCTIONS::SET_VOLUME)
			{
				m_Looper[*iLooper].setVolumeSlider(m_gui_interface.getVolumeSlider());
			}
			else if (applicationState == APPLICATION_FUNCTIONS::SET_PITCH)
			{
				m_Looper[*iLooper].setPitchSlider(m_gui_interface.getPitchSlider());
			}
			else if (applicationState == APPLICATION_FUNCTIONS::SET_PAN)
			{
				m_Looper[*iLooper].setPanSlider(m_gui_interface.getPanSlider());
			}
			else if ((applicationState == APPLICATION_FUNCTIONS::RECORD_FROM_FILE) ||
				     (applicationState == APPLICATION_FUNCTIONS::RECORD_TO_FILE))
			{

			}
			m_Looper[*iLooper].setLooperState(applicationState);
		}

		application->clear();

		m_gui_interface.draw(*application);
		application->display();

	}
	delete[] iLooper;
	delete[] soundBuffer;
	return 0;
}

void ControllerC::drawBaseWindow()
{

}

void ControllerC::kickOffLooperThread(int iThread)
{
	// Prevent us from trying to kick off more threads that we're designed to 
	// handle. 
	if (iThread > MAX_NUMBER_OF_TRACKS)
	{
		std::cout << "Some how we got more threads that we should have." << std::endl;
		return;
	}


}
