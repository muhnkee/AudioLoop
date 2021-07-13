#include "ControllerC.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int ControllerC::run()
{

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works!");
	sf::CircleShape shape(100.f);

	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();

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