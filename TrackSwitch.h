#pragma once
#include "Track.h"
#include <string>
class TrackSwitch : public Track {
private:
	bool Thrown = false;
	bool inTop = false;
	bool inBottom = false;
	std::string dir;
	Track topDetect;
	Track botDetect;
public:
	TrackSwitch(float x, float y, std::string dir) {
		this->dir = dir;
		if (dir == "right") {
			this->track.setSize(sf::Vector2f(150,25));
			this->rotateTrack(45.0);
			this->PlaceTrack(sf::Vector2f(x-5, y));
			this->topDetect.PlaceTrack(sf::Vector2f(x - 105, y));
			this->topDetect.changeColor(sf::Color::Green);
			this->botDetect.PlaceTrack(sf::Vector2f(x + 105, y + 100));
			this->botDetect.changeColor(sf::Color::Blue);
		}
		else if(dir == "left"){
			this->track.setSize(sf::Vector2f(150, 25));
			this->rotateTrack(180-45.0);
			this->PlaceTrack(sf::Vector2f((x+105.0), y + 20));
			this->topDetect.PlaceTrack(sf::Vector2f(105+x, y));
			this->topDetect.changeColor(sf::Color::Green);
			this->botDetect.PlaceTrack(sf::Vector2f(x - 105, y + 100));
			this->botDetect.changeColor(sf::Color::Blue);
		}
	

	}

	bool isClicked(sf::Vector2i mousePos) {
		return this->track.getGlobalBounds().contains(mousePos.x, mousePos.y);
	}

	void throwSwitch(sf::Vector2i mousePos) {
		if (this->isClicked(mousePos)) {
			if (this->Thrown) {
				this->track.setFillColor(sf::Color::Black);
				this->botDetect.changeColor(sf::Color::Black);
				this->topDetect.changeColor(sf::Color::Black);
				this->Thrown = false;
			}
			else {
				this->track.setFillColor(sf::Color::Red);
				this->botDetect.changeColor(sf::Color::Red);
				this->topDetect.changeColor(sf::Color::Red);
				this->Thrown = true;
			}
		}
	}

	void trainDetect(Train train) {
		if (this->topDetect.hasTrain(train)) {
			this->inTop = true;
		}else {
			this->inTop = false;
		}
		if (this->botDetect.hasTrain(train)) {
			this->inBottom = true;
		}
		else {
			this->inBottom = false;
		}
	}

	void topMovement(Train* train) {
		if (this->dir == "left") {
			train->moveDownLeft();
			train->setCrossOver(true);
			return;
		}
		if (this->dir == "right") {
			train->moveDownRight();
			train->setCrossOver(true);
			return;
		}
	}

	void bottomMovement(Train* train) {
		if (this->dir == "left") {
			train->moveUpLeft();
			std::cout << train->getPosition().x <<" "<< train->getPosition().y << std::endl;
			train->setCrossOver(true);
			return;
		}
		if (this->dir == "right") {
			train->moveUpRight();
			train->setCrossOver(true);
			return;
		}
	}

	bool isThrown() {
		return Thrown;
	}
	void debugDraw(sf::RenderWindow& window) {
		this->topDetect.draw(window);
		this->botDetect.draw(window);
	}

	
	Track getTop() {
		return this->topDetect;
	}
	Track getBot() {
		return this->botDetect;
	}

	bool isTop() {
		return inTop;
	}
	bool isBottom() {
		return this->inBottom;
	}
	
};