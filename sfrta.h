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
		vector<TrackSwitch>ts_1;
		TrackSwitch sw(1750.0 - (105.0 * 2), 100.0, "left");
		TrackSwitch sw2(1750.0 - (105.0 * 4), 100.0, "right");
		ts_1.push_back(sw);
		ts_1.push_back(sw2);
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
						if (amtrak.getAngle() != 0 && !amtrak.isRight()) {
							amtrak.moveToLeft();
							break;
						}
						if(amtrak.getAngle()!= 0 && amtrak.isRight()) {
							amtrak.moveToRight();
							break;
						}
						for (int i = 0; i < ts_1.size(); i++) {
							if (!amtrak.getCrossOver() && ts_1[i].isThrown()) {
								//Movement thing
								if (ts_1[i].isTop() && !amtrak.isRight()) {
									ts_1[i].topMovement(&amtrak);
								}
								if (ts_1[i].isBottom() && amtrak.isRight()) {
									ts_1[i].bottomMovement(&amtrak);
								}
							}							
						}
						if (!amtrak.getCrossOver()) {
							amtrak.move();
						}
						
					}
					break;
				case sf::Event::MouseButtonPressed:
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						for (int i = 0; i < sigs_1.size(); i++) {
							sigs_1[i].ChangeLight(sf::Mouse::getPosition(window));
						}
						for (int i = 0; i < ts_1.size(); i++) {
							ts_1[i].throwSwitch(sf::Mouse::getPosition(window));

						}
					}
				}					
			}
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
				for (int i = 0; i < ts_1.size(); i++) {
					ts_1[i].trainDetect(amtrak);
				}

				window.clear(sf::Color(169, 169, 169));
				DrawTrackSwitches(ts_1, window);
				DrawSignals(sigs_1, window);
				DrawSignals(sigs_2, window);
				DrawTrackSwitches(ts_1, window);
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
	}

	void DrawSignals(vector<Signal> sigs, sf::RenderWindow& window) {
		for (Signal s : sigs)
		{
			s.Draw(window);
		}
	}
	void DrawTrackSwitches(vector<TrackSwitch> ts, sf::RenderWindow& window) {
		for (TrackSwitch t : ts) {
			t.draw(window);
			t.debugDraw(window);
		}
	}
};
