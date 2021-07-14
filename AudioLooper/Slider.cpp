#pragma once
#include "DEFINITIONS.h"
#include "Slider.h"

Slider::Slider() {
	level = .5;
	landscape = false;

	bar.loadFromFile(SLIDE_BAR);
	bar_sprite.setTexture(bar);
	bar_sprite.setPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);

	slide.loadFromFile(SLIDE);
	slide_sprite.setTexture(slide);
	slide_sprite.setScale(sf::Vector2f(0.44f, 0.44f));


	double slide_position_x = bar_sprite.getPosition().x;
	double slide_position_y = bar_sprite.getPosition().y + bar_sprite.getGlobalBounds().height / 2 - slide_sprite.getGlobalBounds().height / 2;
	slide_sprite.setPosition(slide_position_x, slide_position_y);
}

Slider::Slider(double widthIn, double heightIn, bool makeLandscape) {
	landscape = makeLandscape;

	bar.loadFromFile(SLIDE_BAR);
	bar_sprite.setTexture(bar);
	bar_sprite.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

	slide.loadFromFile(SLIDE);
	slide_sprite.setTexture(slide);
	slide_sprite.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	
	//outerShape.setSize(sf::Vector2f(800, 800));
	//outerShape.setPosition(sf::Vector2f(x_coord, y_coord));
	//outerShape.setFillColor(sf::Color::Green);

}



void Slider::setSizeScale(double scale_value) {
	bar_sprite.setScale(sf::Vector2f(scale_value, scale_value));
	slide_sprite.setScale(sf::Vector2f(scale_value/2.5, scale_value/2.5));

	//Adjusting the size means we have to update the relative position of the slide as well
	double slide_position_x = bar_sprite.getPosition().x + bar_sprite.getGlobalBounds().width / 11.5;
	double slide_position_y = bar_sprite.getPosition().y + bar_sprite.getGlobalBounds().height / 2 - slide_sprite.getGlobalBounds().height / 2;;
	slide_sprite.setPosition(slide_position_x, slide_position_y);
}

void Slider::setPosition(double coord_x, double coord_y)
{
	bar_sprite.setPosition(coord_x, coord_y);
	double slide_position_x = coord_x + bar_sprite.getGlobalBounds().width / 11.5;
	double slide_position_y = coord_y + bar_sprite.getGlobalBounds().height / 2 - slide_sprite.getGlobalBounds().height / 2;;
	slide_sprite.setPosition(slide_position_x, slide_position_y);
}

void Slider::draw(sf::RenderWindow& window) {
	window.draw(bar_sprite);
	window.draw(slide_sprite);
}