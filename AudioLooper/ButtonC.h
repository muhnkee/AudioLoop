#pragma once
#include <SFML/Graphics.hpp>

class ButtonC
{
public:
	ButtonC(int sizeX, int sizeY);

	sf::Sprite getButtonSprite() { return buttonSprite; };

	sf::IntRect Box; 

	void setButtonColor(int Red, int Green, int Blue, bool isTransparent);
	void setButtonPosition(float xPosition, float yPosition);

	const bool IsClicked(const sf::Mouse Mouse, const float X, const float Y)
	{
		if (!Mouse.isButtonPressed(sf::Mouse::Left))
		{
			return false;
		}
		return Box.contains(X, Y);
	}

private:
	sf::Sprite buttonSprite;
};

