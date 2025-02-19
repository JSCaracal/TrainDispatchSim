#pragma once
#include <SFML/graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
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
	bool atSignal;

public:
	Train(std::string id) {
		identifier = id;
		shape.setSize(sf::Vector2f(25, 15));
		shape.setFillColor(sf::Color::Red);
		shape.setPosition(sf::Vector2f(1750 - 66, 105));
		line.setSize(sf::Vector2f(2.5, 20));
		line.setPosition(sf::Vector2f(1750 - 40, 75));
		line.rotate(45.0);
		font.loadFromFile("./entities/Technology.ttf");
		displayText.setFont(font);
		displayText.setString(identifier);
		displayText.setPosition(sf::Vector2f(1750 - 40, 45));
	}

	~Train() {

	}

	void  move() {
		if (!this->atSignal) {
			std::cout << "Should be moving" << std::endl;
			shape.setPosition(shape.getPosition().x - 105, shape.getPosition().y);
			line.setPosition(line.getPosition().x - 105, line.getPosition().y);
			displayText.setPosition(displayText.getPosition().x - 105, displayText.getPosition().y);
		}
		if (this->getPosition().x < 0) {
			this->setPosition(1750, this->getPosition().y +200.0);
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

	sf::Vector2f  getPosition() {
		return this->shape.getPosition();
	}
};