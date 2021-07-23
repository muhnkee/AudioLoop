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
			// TODO, pull back the event being handled and set the appropriate state 
			// in the corresponding looper
			m_Looper[*iLooper].setLooperState(m_gui_interface.handleEvent(event, iLooper));
		}

		application->clear();

		m_gui_interface.draw(*application);
		application->display();

	}

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
