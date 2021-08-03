#pragma once
#include "DEFINITIONS.h"
#include "Slider.h"
#include <stdio.h>
#include <iostream>

Slider::Slider() {
	level = .5;
	landscape = false;
	selected = false;
}

/// <summary>
/// Sets the orientation for this slider and loads in the correct textures
/// </summary>
/// <param name="makeLandscape"> -true/false if we want a horizontal slider</param>
void Slider::setOrientation(bool makeLandscape) {
	landscape = makeLandscape;
	if (!makeLandscape)
	{
		bar.loadFromFile(SLIDE_BAR);
		bar_sprite.setTexture(bar);
		bar_sprite.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

		slide.loadFromFile(SLIDE);
		slide_sprite.setTexture(slide);
		slide_sprite.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
	else
	{
		bar.loadFromFile(SLIDE_BAR_LANDSCAPE);
		bar_sprite.setTexture(bar);
		bar_sprite.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

		slide.loadFromFile(SLIDE_LANDSCAPE);
		slide_sprite.setTexture(slide);
		slide_sprite.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
}

/// <summary>
/// Indicate the desired size, relative to the gui window size, of this Slider
/// </summary>
/// <param name="scale_value"> -The size relative to the gui window</param>
void Slider::setSizeScale(double scale_value) {
	bar_sprite.setScale(sf::Vector2f(scale_value, scale_value));
	slide_sprite.setScale(sf::Vector2f(scale_value/2.5, scale_value/2.5));

	// Adjusting the size means we have to update the relative position of the slide as well
	double slide_position_x = bar_sprite.getPosition().x + bar_sprite.getGlobalBounds().width / 11.5;
	double slide_position_y = bar_sprite.getPosition().y + bar_sprite.getGlobalBounds().height / 2 - slide_sprite.getGlobalBounds().height / 2;;
	slide_sprite.setPosition(slide_position_x, slide_position_y);
}


/// <summary>
/// Tell where this Slider will be placed in the gui. 
/// Since the slide and the bar are 2 separate sprites, this function ensures that
/// the slide will always start out in the center of the bar.
/// </summary>
/// <param name="coord_x"> -The x-axis coord in the gui where Slider will be placed</param>
/// <param name="coord_y"> -The y-axis coord in the gui where Slider will be placed</param>
void Slider::setInitialPosition(double coord_x, double coord_y)
{
	if (!landscape)
	{
		bar_sprite.setPosition(coord_x, coord_y);
		// more math so that slider always starts out in the center of the bar, no matter the starting position
		double slide_position_x = coord_x + bar_sprite.getGlobalBounds().width / 11.5;
		double slide_position_y = coord_y + bar_sprite.getGlobalBounds().height / 2 - slide_sprite.getGlobalBounds().height / 2;
		slide_sprite.setPosition(slide_position_x, slide_position_y);
	}
	else
	{
		bar_sprite.setPosition(coord_x, coord_y);
		// more math so that slider always starts out in the center of the bar, no matter the starting position
		double slide_position_x = coord_x + bar_sprite.getGlobalBounds().width / 2.2;
		double slide_position_y = coord_y + bar_sprite.getGlobalBounds().height / 2 - slide_sprite.getGlobalBounds().height / 2.07;
		slide_sprite.setPosition(slide_position_x, slide_position_y);
	}
	
}


/// <summary>
/// Getter for finding if this Slider is being selected by a mouse
/// </summary>
/// <returns>bool - if this Slider is currently selected</returns>
bool Slider::isSelected() {
	return selected;
}

/// <summary>
/// Getter for accessing this Slider's slide_sprite
/// </summary>
/// <returns>Pointer to this slide_sprite</returns>
sf::Sprite* Slider::getSliderSprite() {
	return &slide_sprite;
}

/// <summary>
///  Tell this Slider that the slide needs to follow the mouse
/// </summary>
void Slider::followMouse() {
	selected = true;
}

/// <summary>
/// Tell this Slider that the slide needs to stop following the mouse
/// </summary>
void Slider::stopFollowingMouse() {
	selected = false;
}

/// <summary>
/// Get the current level of this slide bar
/// </summary>
/// <returns>double - The percentage of the slider </returns>
double Slider::getLevel()
{
	return level;
}
/// <summary>
/// Set the current level of this slide bar based on the sliders current relative
///  position
/// </summary>
void Slider::setLevel()
{
	if (!landscape)
	{
		double relative_position = slide_sprite.getPosition().y - bar_sprite.getPosition().y;
		// subtract by 1 b/c we want the top of the slidebar to == 1.0 and bottom to be 0.0 
		// and the y value increase 'downward' in the window
		level = 1.0 - (relative_position / bar_sprite.getGlobalBounds().height);

		// b/c the slider has "mass", it never actually gets to 0
		// .0876 is the lowest it will go, but can sometimes be .0903 as well
		if (level < .088) {
			level = 0;
		}
	}
	else
	{
		double start_coords = bar_sprite.getPosition().x;
		double end_coords = bar_sprite.getPosition().x + bar_sprite.getGlobalBounds().width;

		double relative_slide_position = slide_sprite.getPosition().x - start_coords;
		double relative_end_position = end_coords - start_coords;

		level = (relative_slide_position + slide_sprite.getGlobalBounds().width) / bar_sprite.getGlobalBounds().width;
		// b/c the slider has "mass", it never actually gets to 0
		// .0876 is the lowest it will go, but can sometimes be .0903 as well
		if (level < .0882) {
			level = 0;
		}
		// same logic as above, but with upper bound (landscape only)
		if (level > .995) {
			level = 1;
		}
	}
#ifdef DEBUG
	std::cout << "level = " << level << std::endl;
#endif // DEBUG
}

/// <summary>
/// Ajusts the position of the slide according to the mouse location, y axis only
/// </summary>
/// <param name="mouse_x"> -The location of the mouse in the x-axis</param>
/// <param name="mouse_y"> -The location of the mouse in the y-axis</param>
void Slider::move_slide(double mouse_x, double mouse_y) {
	if (!landscape)
	{
		// doing this math so that the slider is always in the middle of the bar
		double slide_position_x = bar_sprite.getPosition().x + bar_sprite.getGlobalBounds().width / 11.5;
		slide_sprite.setPosition(slide_position_x, mouse_y);
	}
	else //TODO: DEBUG
	{
		// doing this math so that the slider is always in the middle of the bar
		double slide_position_y = bar_sprite.getPosition().y + bar_sprite.getGlobalBounds().height / 11.5;
		slide_sprite.setPosition(mouse_x, slide_position_y);
	}
	// update the level component to track intensity
	setLevel();
}

/// <summary>
/// Renders all Slider components to the gui window
/// </summary>
/// <param name="window"> -Where we will draw</param>
void Slider::draw(sf::RenderWindow& window) {
	window.draw(bar_sprite);

	if (selected) {
		if (!landscape)
		{
			double upperBound = sf::Mouse::getPosition(window).y;
			double lowerBound = sf::Mouse::getPosition(window).y + slide_sprite.getGlobalBounds().height;
			if (bar_sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, upperBound))
			{
				if (bar_sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, lowerBound))
				{
					move_slide(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				}
			}
		}
		else
		{
			double upperBound = sf::Mouse::getPosition(window).x;
			double lowerBound = sf::Mouse::getPosition(window).x + slide_sprite.getGlobalBounds().width;
			if (bar_sprite.getGlobalBounds().contains(upperBound, sf::Mouse::getPosition(window).y))
			{
				if (bar_sprite.getGlobalBounds().contains(lowerBound, sf::Mouse::getPosition(window).y))
				{
					move_slide(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				}
			}
		}
		
	}
	window.draw(slide_sprite);
}

/// <summary>
/// Identifying information on this slider,  should be some sort of unique key
/// </summary>
/// <param name="nameIn"> -a key name for this Slider</param>
void Slider::setName(std::string nameIn)
{
	name = nameIn;
}

/// <summary>
/// Get the name of this slider
/// </summary>
/// <returns>string -the name</returns>
std::string Slider::getName()
{
	return name;
}
