#pragma once
#include "DEFINITIONS.h"
#include "MusicSeek.h"
#include <stdio.h>
#include <iostream>

MusicSeek::MusicSeek() {
	level = .5;
	landscape = false;
	selected = false;
	looperAudioTrack = nullptr;

	bar.loadFromFile(MUSIC_SEEK_BAR);
	bar_sprite.setTexture(bar);
	bar_sprite.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	slide.loadFromFile(MUSIC_SEEK_SLIDE);
	slide_sprite.setTexture(slide);
	slide_sprite.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}


/// <summary>
/// Indicate the desired size, relative to the gui window size, of this Slider
/// </summary>
/// <param name="scale_value"> -The size relative to the gui window</param>
void MusicSeek::setSizeScale(double scale_value) {
	bar_sprite.setScale(sf::Vector2f(scale_value, scale_value));
	slide_sprite.setScale(sf::Vector2f(scale_value * 1.2, scale_value *1.4));

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
void MusicSeek::setInitialPosition(double coord_x, double coord_y)
{
	bar_sprite.setPosition(coord_x, coord_y);
	// more math so that slider always starts out in the center of the bar, no matter the starting position
	double slide_position_x = coord_x + bar_sprite.getGlobalBounds().width / 2.2;
	double slide_position_y = coord_y + bar_sprite.getGlobalBounds().height / 2 - slide_sprite.getGlobalBounds().height / 2.07;
	slide_sprite.setPosition(slide_position_x, slide_position_y);
}


/// <summary>
/// Getter for finding if this Slider is being selected by a mouse
/// </summary>
/// <returns>bool - if this Slider is currently selected</returns>
bool MusicSeek::isSelected() {
	return selected;
}

/// <summary>
/// Getter for accessing this Slider's slide_sprite
/// </summary>
/// <returns>Pointer to this slide_sprite</returns>
sf::Sprite* MusicSeek::getSliderSprite() {
	return &slide_sprite;
}

/// <summary>
///  Tell this Slider that the slide needs to follow the mouse
/// </summary>
void MusicSeek::followMouse() {
	selected = true;
}

/// <summary>
/// Tell this Slider that the slide needs to stop following the mouse
/// </summary>
void MusicSeek::stopFollowingMouse() {
	selected = false;
}

/// <summary>
/// Renders all Slider components to the gui window
/// </summary>
/// <param name="window"> -Where we will draw</param>
void MusicSeek::draw(sf::RenderWindow& window) {
	window.draw(bar_sprite);

	if (looperAudioTrack) {
		// offset starting x so that we start within the bar
		double bar_sprite_x_offset = bar_sprite.getPosition().x + slide_sprite.getGlobalBounds().width;

		sf::Time lowerBound = looperAudioTrack->getPlayingOffset();
		sf::Time upperBound = looperAudioTrack->getDuration();

		double percentage = (lowerBound / upperBound) * .95; // multiply by .95 so we don't run past the texture boundaries
		double slide_position_x = bar_sprite_x_offset + (percentage * bar_sprite.getGlobalBounds().width);
		double slide_position_y = bar_sprite.getPosition().y + bar_sprite.getGlobalBounds().height / 2 - slide_sprite.getGlobalBounds().height / 2;
		slide_sprite.setPosition(slide_position_x, slide_position_y);
	}
	else {
		double slide_position_y = bar_sprite.getPosition().y + bar_sprite.getGlobalBounds().height / 2 - slide_sprite.getGlobalBounds().height / 2;
		double bar_sprite_x_offset = bar_sprite.getPosition().x + slide_sprite.getGlobalBounds().width;

		slide_sprite.setPosition(bar_sprite_x_offset, slide_position_y);
	}
	window.draw(slide_sprite);
}

void MusicSeek::setMusicTrack(sf::Music* audioTrackPtr) {
	looperAudioTrack = audioTrackPtr;
}