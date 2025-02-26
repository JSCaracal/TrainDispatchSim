#pragma once
#include <SFML/Graphics.hpp>
#include "vector"
#include "Train.h"
#define TRACK_LENGTH 100.0

/*
* All Functions are Created by Joshua Sipos
* Track.h
*/

class Track {

protected:
	sf::RectangleShape track;
	sf::Vector2f pos;

public:
	Track() {
		track.setSize(sf::Vector2f(TRACK_LENGTH, 25));
		track.setFillColor(sf::Color::Black);
	}

	Track(float length) {
		track.setSize(sf::Vector2f(length, 25));
		track.setFillColor(sf::Color::Black);
	}


	Track(bool hasSig) {
		track.setSize(sf::Vector2f(120, 25));
		track.setFillColor(sf::Color::Black);

	}

	void  PlaceTrack(sf::Vector2f coords) {
		track.setPosition(coords);
	}


	void rotateTrack(float angle) {
		track.rotate(angle);
	}

	bool hasTrain(Train train) {
		return this->track.getGlobalBounds().contains(train.getPosition());
	}

	void  draw(sf::RenderWindow& window) {
		window.draw(track);
	}
	void changeColor(sf::Color c) {
		this->track.setFillColor(c);
	}

	sf::RectangleShape getShape() {
		return this->track;
	}
	
	sf::Vector2f  GetCoords() {
		return track.getPosition();
	}

};