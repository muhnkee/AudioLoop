#pragma once
#include "DEFINITIONS.h"
#include "Slider.h"

Slider::Slider() {
	level = .5;
	landscape = false;
	selected = false;

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
	level = .5;
	landscape = makeLandscape;
	selected = false;

	bar.loadFromFile(SLIDE_BAR);
	bar_sprite.setTexture(bar);
	bar_sprite.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

	slide.loadFromFile(SLIDE);
	slide_sprite.setTexture(slide);
	slide_sprite.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
}



void Slider::setSizeScale(double scale_value) {
	bar_sprite.setScale(sf::Vector2f(scale_value, scale_value));
	slide_sprite.setScale(sf::Vector2f(scale_value/2.5, scale_value/2.5));

	// Adjusting the size means we have to update the relative position of the slide as well
	double slide_position_x = bar_sprite.getPosition().x + bar_sprite.getGlobalBounds().width / 11.5;
	double slide_position_y = bar_sprite.getPosition().y + bar_sprite.getGlobalBounds().height / 2 - slide_sprite.getGlobalBounds().height / 2;;
	slide_sprite.setPosition(slide_position_x, slide_position_y);
}

void Slider::setInitialPosition(double coord_x, double coord_y)
{
	bar_sprite.setPosition(coord_x, coord_y);
	// more math so that slider always starts out in the center of the bar, no matter the starting position
	double slide_position_x = coord_x + bar_sprite.getGlobalBounds().width / 11.5;
	double slide_position_y = coord_y + bar_sprite.getGlobalBounds().height / 2 - slide_sprite.getGlobalBounds().height / 2;;
	slide_sprite.setPosition(slide_position_x, slide_position_y);
}

void Slider::setSliderPosition(double coord_x, double coord_y)
{

}

bool Slider::isSelected() {
	return selected;
}

sf::Sprite* Slider::getSliderSprite() {
	return &slide_sprite;
}

void Slider::followMouse() {
	selected = true;
}
void Slider::stopFollowingMouse() {
	selected = false;
}

double Slider::getLevel()
{
	return level;
}
void Slider::setLevel()
{
	//TODO: do calculation based on where the slider is relative to the height of the bar
}

void Slider::move_slide(double mouse_y) {
	// doing this math so that the slider is always in the middle of the bar
	double slide_position_x = bar_sprite.getPosition().x + bar_sprite.getGlobalBounds().width / 11.5;
	slide_sprite.setPosition(slide_position_x, mouse_y);
}

void Slider::draw(sf::RenderWindow& window) {
	window.draw(bar_sprite);

	if (selected) {
		double upperBound = sf::Mouse::getPosition(window).y;
		double lowerBound = sf::Mouse::getPosition(window).y + slide_sprite.getGlobalBounds().height;
		if (bar_sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, upperBound))
		{
			if (bar_sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, lowerBound))
			{
				move_slide(sf::Mouse::getPosition(window).y);
				// update the level component to track intensity
				setLevel();
			}
		}
	}
	window.draw(slide_sprite);
}