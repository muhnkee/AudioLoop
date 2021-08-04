#pragma once
#include <SFML/Graphics.hpp>

class ButtonC
{
public:
	ButtonC();

	sf::Sprite* getButtonSprite() { return &buttonSprite; };
	std::string getName() { return name; };
	bool isActive() { return active; };
	bool IsClicked(const sf::Mouse Mouse, const float X, const float Y);
	bool isEnabled() { return enabled; };
	void setSizeScale(double scaleValue);
	void setButtonPosition(float xPosition, float yPosition);
	void setTexture(std::string fileName);
	void setName(std::string nameIn);
	void setEnabled(bool toggle);

	void draw(sf::RenderWindow& window);

	//void isClicked();
	

private:
	bool active;
	bool enabled;
	sf::Sprite buttonSprite;
	sf::Texture buttonTexture;
	std::string name;
};

