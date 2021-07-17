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

	while (application->isOpen())
	{
		sf::Event event;
		sf::SoundBuffer *soundBuffer; 

		while (application->pollEvent(event))
		{
			m_gui_interface.handleEvent(event);
			//m_Looper[1]->setSoundBuffer(soundBuffer);

			//m_Looper[1].Launch();
		}

		application->clear();
		//application.draw(playButton.getButtonSprite());
		//application.draw(shape);
		m_gui_interface.draw(*application);
		application->display();

	}

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
