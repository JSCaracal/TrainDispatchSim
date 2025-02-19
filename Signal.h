#pragma once
#include <SFML/Graphics.hpp>
#include "Track.h"
class Signal
{
private:
	sf::CircleShape light;
	Track track;
public:
	Signal(Track t) {
		light.setRadius(15);
		light.setFillColor(sf::Color::Green);
		light.setOutlineColor(sf::Color::Black);
		light.setOutlineThickness(2);
		this->track = t;
		sf::Vector2f trackPos = t.GetCoords();
		light.setPosition(trackPos.x + 25, trackPos.y - 50);
	}
	void  ChangeLight(sf::Vector2i mousePos) {
		if (this->isMouse(mousePos)) {
			if (this->light.getFillColor() == sf::Color::Green) {
				this->light.setFillColor(sf::Color::Red);
			}
			else {
				this->light.setFillColor(sf::Color::Green);
			}
		}
	}

	bool  isRed() {
		if (this->light.getFillColor() == sf::Color::Red) {
			return true;
		}
		else {
			return false;
		}
	}

	bool  isMouse(sf::Vector2i mousePos) {
		return this->light.getGlobalBounds().contains(mousePos.x, mousePos.y);
	}
	void  Draw(sf::RenderWindow& window) {
		window.draw(light);
	}

	sf::CircleShape  getLight() {
		return light;
	}
	Track getTrack() {
		return track;
	}
};