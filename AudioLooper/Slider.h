#pragma once
#include <SFML/Graphics.hpp>

class Slider {
public:
	Slider();
	Slider(double widthIn, double heightIn, bool makeLandscape = false);

	void move_slide(double mouse_y);

	void setPosition(double coord_x, double coord_y);
	void setSizeScale(double scale_value);

	void draw(sf::RenderWindow& window);

private:
	bool landscape;
	sf::Texture bar;
	sf::Sprite bar_sprite;
	sf::Texture slide;
	sf::Sprite slide_sprite;


	sf::RectangleShape outerShape;

	// the indicator of where the slide is on the bar
	double level;
};