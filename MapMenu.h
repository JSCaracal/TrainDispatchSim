#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "sfrta.h"
#define MAP_COUNT 2
class MapMenu
{
private:
	sf::Font font;
	sf::Text mapText[MAP_COUNT + 1];
	sf::Sprite mapImage[MAP_COUNT];
	sf::Texture sfrtaTexture;
	sf::Texture cfcrcTexture;
	int mapSelection;
	void  CreateMenu() {
		if (!font.loadFromFile("entities/RubikMonoOne-Regular.ttf")) {
			std::cout << "Missing font" << std::endl;
		}
		mapText[0].setFont(font);
		mapText[0].setFillColor(sf::Color::Blue);
		mapText[0].setString("SFRTA");
		mapText[0].setCharacterSize(70);

		sfrtaTexture.loadFromFile("entities/sfrta.jpg");
		mapImage[0].setTexture(sfrtaTexture);
		mapImage[0].setPosition(100, 200);
		mapImage[0].setScale(.6, .6);
		mapText[0].setPosition(300, 700);
		mapText[1].setFont(font);
		mapText[1].setFillColor(sf::Color::White);
		mapText[1].setString("CFCRC");
		mapText[1].setCharacterSize(70);
		mapText[1].setPosition(1100, 700);

		cfcrcTexture.loadFromFile("entities/CFCRC.jpg");
		mapImage[1].setTexture(cfcrcTexture);
		mapImage[1].setPosition(850, 200);
		mapImage[1].scale(.6, .74);

		mapText[2].setFont(font);
		mapText[2].setFillColor(sf::Color::White);
		mapText[2].setString("Exit");
		mapText[2].setCharacterSize(20);
		mapText[2].setPosition(50, 10);
	}

	void  draw(sf::RenderWindow& window) {
		for (int i = 0; i < MAP_COUNT; i++) {
			window.draw(mapText[i]);
			window.draw(mapImage[i]);
		}
		window.draw(mapText[2]);

	}

	void  SelectRight() {
		if (mapSelection + 1 <= MAP_COUNT + 1) {
			mapText[mapSelection].setFillColor(sf::Color::White);
			mapSelection++;
			if (mapSelection == MAP_COUNT + 1) {
				mapSelection = 0;
			}
			mapText[mapSelection].setFillColor(sf::Color::Blue);
		}
	}

	void  SelectLeft() {
		if (mapSelection >= 0) {
			mapText[mapSelection].setFillColor(sf::Color::White);
			mapSelection--;
			if (mapSelection == -1) {
				mapSelection = 2;
			}
			mapText[mapSelection].setFillColor(sf::Color::Blue);
		}
	}
public:
	MapMenu(float x, float y) {
		sf::RenderWindow mapSelect(sf::VideoMode(x, y), "Select Map");
		CreateMenu();
		mapSelection = 0;
		while (mapSelect.isOpen()) {
			sf::Event event;
			while (mapSelect.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					mapSelect.close();
					break;
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Escape:
						mapSelect.close();
						return;
					case sf::Keyboard::Right:
						SelectRight();
						break;
					case sf::Keyboard::Left:
						SelectLeft();
						break;
					case sf::Keyboard::Return:
						if (mapSelection == 0) {
							sfrta sf(x, y);
							mapSelect.close();
							break;
						}
						if (mapSelection == 1) {
							//Run the cfrcr map
						}
						if (mapSelection == 2) {
							mapSelect.close();
						}
						break;
					default:
						break;
					}
				}
			}
			mapSelect.clear(sf::Color::Black);
			draw(mapSelect);
			mapSelect.display();
		}
	}
};