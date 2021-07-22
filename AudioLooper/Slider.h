#pragma once
#include <SFML/Graphics.hpp>

class Slider {
public:
	Slider();
	Slider(double widthIn, double heightIn, bool makeLandscape = false);

	void move_slide(double mouse_y);

	sf::Sprite* getSliderSprite();
	void setInitialPosition(double coord_x, double coord_y);
	void setSizeScale(double scale_value);
	bool isSelected();

	double getLevel();
	void setLevel();

	void followMouse();
	void stopFollowingMouse();
	void draw(sf::RenderWindow& window);

	void setName(std::string nameIn);
	std::string getName();

private:
	bool landscape;
	bool selected;
	sf::Texture bar;
	sf::Sprite bar_sprite;
	sf::Texture slide;
	sf::Sprite slide_sprite;

	std::string name;

	sf::RectangleShape outerShape;

	// the indicator of where the slide is on the bar
	// ranges from 0.0 to 1.0
	double level;
};