#pragma once
#include "Track.h"
class TrackSwitch : public Track {
private:
	bool isThrown;
public:
	TrackSwitch(float x, float y) {
		this->rotateTrack(45.0);
		this->PlaceTrack(sf::Vector2f(x, y));
	}

	bool isClicked(sf::Vector2i mousePos) {
		return this->track.getGlobalBounds().contains(mousePos.x, mousePos.y);
	}

	void throwSwitch() {
		if (this->isThrown) {
			this->track.setFillColor(sf::Color::Black);
		}
		else {
			this->track.setFillColor(sf::Color::Red);
		}
	}
	
};