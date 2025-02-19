#include <SFML/Graphics.hpp>
#include "sfrta.h"
#include "Homescreen.h"
#include "MapMenu.h"
int main() {
	const int WIDTH = 1750;
	const int HEIGHT = WIDTH / 2.2;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Railway Dispatch Alpha 0.2", sf::Style::Close | sf::Style::Titlebar);
	sf::Texture mainMenuBG;
	sfrta::sfrta(WIDTH, HEIGHT);
	Homescreen menu(window.getSize().x, window.getSize().y);

	while (window.isOpen()) {
		window.setKeyRepeatEnabled(false);
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code) {
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;
				case sf::Keyboard::Down:
					menu.MoveDown();
					break;
				case sf::Keyboard::Return:
					if (menu.OptionSelected() == 0) {
						MapMenu mm(window.getSize().x, window.getSize().y);
						window.close();
						break;
					}
					if (menu.OptionSelected() == 1) {
						window.close();
						break;
					}

				}
			}


		}

		window.clear();
		menu.draw(window);
		window.display();
	}
	return 0;
}