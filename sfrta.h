#pragma once
#define N_SEGS 17
#include <SFML/Graphics.hpp>
#include "Signal.h"
#include "Train.h"
#include "Signal.h"
#include "Track.h"
#include "TrackSwitch.h"
using namespace std;
class sfrta {
public: 
	sfrta(float x, float y) {
		sf::RenderWindow window(sf::VideoMode(x, y), "Dispatch Game");
		vector<Signal>sigs_1 = CreateSignals(N_SEGS, 100);
		vector<Signal>sigs_2 = CreateSignals(N_SEGS, 200);
		vector<Train> traffic;
		Train amtrak = Train("Q844");
		while (window.isOpen()) {
			sf::Event event;
			window.setKeyRepeatEnabled(false);
			while (window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyReleased:
					switch (event.key.code) {
						//This is a simulation of train movement
					case sf::Keyboard::W:
						for (Signal s : sigs_1) {
							if (s.getTrack().hasTrain(amtrak)) {
								if (s.isRed()) {
									amtrak.setSig(true);
								}
								else {
									amtrak.setSig(false);
								}
							}
						}
						amtrak.move();
						break;
					}
				case sf::Event::MouseButtonPressed:
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						for (int i = 0; i < sigs_1.size(); i++) {
							sigs_1[i].ChangeLight(sf::Mouse::getPosition(window));
						}
					}

				}
			}

			window.clear(sf::Color(169, 169, 169));
			DrawSignals(sigs_1, window);
			DrawSignals(sigs_2, window);
			CreateWorld(window);
			amtrak.Draw(window);
			window.display();
		}
	}
	vector<Signal>CreateSignals(int track_num, int height) {
		vector<Signal>sigs;
		for (int i = 1; i <= track_num; i++) {
			if (i % 3 == 0) {
				Track t = new Track();
				t.PlaceTrack(sf::Vector2f(1750 - ((100.0 + 5) * i), height));
				Signal s(t);
				sigs.push_back(s);
			}
		}
		return sigs;
	}

	void CreateWorld(sf::RenderWindow& window) {
		float len = 100.0;
		for (int x = 1; x <= N_SEGS; x++) {
			Track t1(len);
			t1.PlaceTrack(sf::Vector2f(1750 - ((len + 5) * x), 100));
			t1.draw(window);
		}
		for (int x = 1; x <= N_SEGS; x++) {
			Track t2(len);
			t2.PlaceTrack(sf::Vector2f(1750 - ((len + 5) * x), 200));
			t2.draw(window);
		}
		TrackSwitch sw(1500.0,110.0);
		sw.draw(window);
	}

	void DrawSignals(vector<Signal> sigs, sf::RenderWindow& window) {
		for (Signal s : sigs)
		{
			s.Draw(window);
		}
	}
};
