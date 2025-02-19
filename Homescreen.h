#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
class Homescreen
#define Max_Homescreen 3
{
public:
	 Homescreen(float width, float height) {
		if (!font.loadFromFile("entities/RubikMonoOne-Regular.ttf")) {
			std::cout << "Missing font" << std::endl;
		}
		/*Gets Background image*/

		bgtexture.loadFromFile("entities/bgdispatch.jpg");

		bgrender.setTexture(bgtexture);
		bgrender.setScale(width / bgtexture.getSize().x, height / bgtexture.getSize().y);
		/*Play Game*/
		HomescreenText[0].setFont(font);
		HomescreenText[0].setFillColor(sf::Color::Black);
		HomescreenText[0].setString("Play");
		HomescreenText[0].setCharacterSize(70);
		HomescreenText[0].setPosition(400, 200);
		/*Exit*/
		HomescreenText[1].setFont(font);
		HomescreenText[1].setFillColor(sf::Color::Blue);
		HomescreenText[1].setString("Exit");
		HomescreenText[1].setCharacterSize(70);
		HomescreenText[1].setPosition(400, 300);
		/*About*/
		HomescreenText[2].setFont(font);
		HomescreenText[2].setFillColor(sf::Color::Black);
		HomescreenText[2].setString("About");
		HomescreenText[2].setCharacterSize(70);
		HomescreenText[2].setPosition(400, 400);
		option = 1;
	}

	 ~Homescreen() {

	}

	void  draw(sf::RenderWindow& window) {
		window.draw(bgrender);
		for (int i = 0; i < Max_Homescreen; i++) {
			window.draw(HomescreenText[i]);
		}

	}

	void  MoveUp() {
		if (option >= 0) {
			HomescreenText[option].setFillColor(sf::Color::Black);
			option--;
			if (option == -1) {
				option = 2;
			}
			HomescreenText[option].setFillColor(sf::Color::Blue);
		}

	}

	void  MoveDown() {
		if (option + 1 <= Max_Homescreen) {
			HomescreenText[option].setFillColor(sf::Color::Black);
			option++;
			if (option == Max_Homescreen) {
				option = 0;
			}
			HomescreenText[option].setFillColor(sf::Color::Blue);
		}

	}
	int  OptionSelected() {
		return option;
	}
private:
	int option;
	sf::Font font;
	sf::Text HomescreenText[Max_Homescreen];
	sf::Texture bgtexture;
	sf::Sprite bgrender;
};