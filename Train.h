#pragma once
#include <SFML/graphics.hpp>
#include "vector"
#include "string"
#include "iostream"
#define RIGHT_START -37.5
#define TRACK 100
class Train
{
private:
	sf::Font font;
	sf::Text displayText;
	sf::RectangleShape shape;
	sf::Text idenDisplay;
	std::string identifier;
	std::vector<std::string> stopInstructions;
	sf::RectangleShape line;
	sf::Transformable tf;
	bool atSignal;
	bool crossingOver;
	bool movingRight;
	sf::Vector2f origin;
	sf::Vector2f sPos;

public:
	Train(std::string id) {
		identifier = id;
		shape.setSize(sf::Vector2f(25, 15));
		shape.setFillColor(sf::Color::Yellow);
		shape.setPosition(sf::Vector2f(1750 - 66, 105 + TRACK));
		line.setSize(sf::Vector2f(2.5, 20));
		line.setPosition(sf::Vector2f(1750 - 40, 75 + TRACK));
		line.rotate(45.0);
		font.loadFromFile("./entities/Technology.ttf");
		displayText.setFont(font);
		displayText.setString(identifier);
		displayText.setPosition(sf::Vector2f(1750 - 40, 45+TRACK));
		this->origin = shape.getPosition();
	}

	Train(std::string id, int isRight) {
			identifier = id;
			if (isRight) {
				movingRight = true;
			}
			shape.setSize(sf::Vector2f(25, 15));
			shape.setFillColor(sf::Color::Yellow);
			shape.setPosition(sf::Vector2f(RIGHT_START - 66, 105 + TRACK));
			line.setSize(sf::Vector2f(2.5, 20));
			line.setPosition(sf::Vector2f(RIGHT_START - 40, 75 + TRACK));
			line.rotate(45.0);
			font.loadFromFile("./entities/Technology.ttf");
			displayText.setFont(font);
			displayText.setString(identifier);
			displayText.setPosition(sf::Vector2f(RIGHT_START - 40, 45 + TRACK));
			this->origin = shape.getPosition();
		}

	~Train() {

	}

	void  move() {
		if (!movingRight) {
			if (!this->atSignal) {
				std::cout << "Should be moving" << std::endl;
				shape.setPosition(shape.getPosition().x - 105, shape.getPosition().y);
				line.setPosition(line.getPosition().x - 105, line.getPosition().y);
				displayText.setPosition(displayText.getPosition().x - 105, displayText.getPosition().y);
			}
			if (this->getPosition().x < 0) {
				this->setPosition(1750, this->getPosition().y + 200.0);
			}
		}
		else {
			if (!this->atSignal) {
				std::cout << "Should be moving Right" << std::endl;
				shape.setPosition(shape.getPosition().x + 105, shape.getPosition().y);
				line.setPosition(line.getPosition().x + 105, line.getPosition().y);
				displayText.setPosition(displayText.getPosition().x + 105, displayText.getPosition().y);
			}
			if (this->getPosition().x > 1750) {
				this->setPosition(1750, this->getPosition().y - 200.0);
			}
		}
		

	}


	void moveDownLeft() {
		this->sPos = this->getPosition();
		sf::Vector2f cpos = this->getPosition();
		this->setPosition(cpos.x - 52.5, cpos.y + 130/2);
		this->setAngle(360 - 45);
	}

	void moveDownRight() {
		sf::Vector2f cpos = this->getPosition();
		this->setPosition(cpos.x + 182, cpos.y + 75);
		this->setAngle(225);
	}

	void moveUpLeft() {
		this->sPos = this->getPosition();
		sf::Vector2f cpos = this->getPosition();
		this->setPosition(cpos.x + 196, cpos.y - 50);
		this->setAngle(135);
	}

	void moveUpRight() {
		sf::Vector2f cpos = this->getPosition();
		
		this->setAngle(360-135);
		this->setPosition(cpos.x - 31.5, cpos.y-25);
	}

	void moveToLeft() {
		if (this->getAngle() == 315) {
			sf::Vector2f nPos = this->sPos;
			nPos.x = nPos.x - 105 - 37.5;
			nPos.y = nPos.y + 100;
			this->setAngle(0);
			this->setPosition(nPos.x, nPos.y);
			this->crossingOver = false;
		}
		if (this->getAngle() == 225) {
			sf::Vector2f nPos = this->getPosition();
			nPos.x = nPos.x - 49 ;
			nPos.y = nPos.y -75;
			this->setAngle(0);
			this->setPosition(nPos.x, nPos.y);
			this->crossingOver = false;
		}
		
	}

	void moveToRight() {
		sf::Vector2f tPos = this->getPosition();
		if (this->getAngle() == 135) {
			this->setAngle(0);
			this->crossingOver = false;
			this->setPosition(tPos.x + 150, tPos.y - 50);
			return;
		}
		if (this->getAngle() == 225) {
			sf::Vector2f tPos = this->getPosition();
			this->setAngle(0);
			this->crossingOver = false;
			this->setPosition(tPos.x + 161.5, round(((tPos.y / 100)*100) + 25));
		}
		
	}




	void  Draw(sf::RenderWindow& window) {
		window.draw(shape);
		window.draw(line);
		window.draw(displayText);
	}

	void  setSig(bool isStopped) {
		this->atSignal = isStopped;
	}
	bool isSig() {
		return this->atSignal;
	}

	void setPosition(float x, float y) {
		this->shape.setPosition(x-66, y);
		this->line.setPosition(x-40.0,y-30.0);
		this->displayText.setPosition(x - 40, y - 60.0);
	}

	void setAngle(float r) {
		this->shape.setRotation(r);
		//this->line.setRotation(45 + r);
	}

	bool isRight() {
		return this->movingRight;
	}
	bool getCrossOver() {
		return this->crossingOver;
	}

	void setCrossOver(bool val) {
		this->crossingOver = val;
	}

	sf::Vector2f  getPosition() {
		return this->shape.getPosition();
	}
	float getAngle() {
		return this->shape.getRotation();
	}
};