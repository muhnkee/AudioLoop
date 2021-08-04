#include "ButtonC.h"
#include <SFML/Graphics.hpp>


ButtonC::ButtonC()
{
	active = false;
	enabled = true;
}

void ButtonC::setTexture(std::string fileName)
{
	buttonTexture.loadFromFile(fileName);
	buttonSprite.setTexture(buttonTexture);
}

void ButtonC::setName(std::string nameIn)
{
	name = nameIn;
}


void ButtonC::setButtonPosition(float xPosition, float yPosition)
{
	buttonSprite.setPosition(sf::Vector2f(xPosition, yPosition));
}

void ButtonC::setSizeScale(double scaleValue) {
	buttonSprite.setScale(sf::Vector2f(scaleValue, scaleValue));
}

bool ButtonC::IsClicked(const sf::Mouse Mouse, const float X, const float Y)
{
	if (!Mouse.isButtonPressed(sf::Mouse::Left))
	{
		return false;
	}
	return buttonSprite.getGlobalBounds().contains(X, Y);
}

void ButtonC::setEnabled(bool toggle)
{
	enabled = toggle;
}

void ButtonC::setActive(bool isActive)
{
	active = isActive;
}

void ButtonC::draw(sf::RenderWindow& window) {

	window.draw(buttonSprite);
}