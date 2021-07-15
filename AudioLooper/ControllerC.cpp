#include "ButtonC.h"
#include "ControllerC.h"
#include "DEFINITIONS.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int ControllerC::run()
{
	// Create a window
	//sf::RenderWindow application(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "AudioLooper");
	sf::RenderWindow* application = gui_interface.getWindow();
	// 
	//ButtonC playButton(50, 50);
	//playButton.setButtonColor(255, 0, 255, true);
	//playButton.setButtonPosition(10.f, 50.f);

	application->setMouseCursorVisible(true);
	//sf::CircleShape shape(100.f);

	//shape.setFillColor(sf::Color::Green);

	while (application->isOpen())
	{
		sf::Event event;
		while (application->pollEvent(event))
		{
			gui_interface.handleEvent(event);
		}

		application->clear();
		//application.draw(playButton.getButtonSprite());
		//application.draw(shape);
		gui_interface.draw(*application);
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
	if (iThread > MAX_THREADS)
	{
		std::cout << "Some how we got more threads that we should have." << std::endl;
		return;
	}
}
