#include "ButtonC.h"
#include "ControllerC.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int ControllerC::run()
{
	// Create a window
	sf::RenderWindow application(sf::VideoMode(640, 480, 32), "AudioLooper");
	ButtonC playButton(50, 50);
	playButton.setButtonColor(255, 0, 255, true);
	playButton.setButtonPosition(10.f, 50.f);

	application.setMouseCursorVisible(false);
	sf::CircleShape shape(100.f);

	shape.setFillColor(sf::Color::Green);

	while (application.isOpen())
	{
		sf::Event event;
		while (application.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				application.close();
		}

		application.clear();
		application.draw(playButton.getButtonSprite());
		//application.draw(shape);
		application.display();

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