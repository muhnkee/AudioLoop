#include "ButtonC.h"
#include <SFML/Graphics.hpp>


ButtonC::ButtonC(int sizeX, int sizeY)
{
	sf::Texture buttonTexture;
	if (!(buttonTexture.create(sizeX, sizeY)))
	{
		// error handling tbd
	}
	// Pixels have 4 components, RGBA
	sf::Uint8 *pixels = new sf::Uint8[sizeX * sizeY * 4];
	buttonTexture.update(pixels);

	buttonSprite.setTexture(buttonTexture);
}

void ButtonC::setButtonColor(int Red, int Blue, int Green, bool isTransparent)
{
	if (isTransparent)
	{
		buttonSprite.setColor(sf::Color(Red, Blue, Green, 128));
	}
	else
	{
		buttonSprite.setColor(sf::Color(Red, Blue, Green, 0));

	}
}

void ButtonC::setButtonPosition(float xPosition, float yPosition)
{
	buttonSprite.setPosition(sf::Vector2f(xPosition, yPosition));
}