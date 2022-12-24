#pragma once
#include <SFML/Graphics.hpp>
#include "characters.h" 
#include "FontManager.h"

using namespace std;

class GameScreen
{
public:
	virtual void render(vector<characters> heroes, sf::RenderWindow* window, int gameScore) {};
	virtual void update(sf::Event event, vector<characters>& heroes, int& gameScore) {};
	bool isRunning() { return this->_rinning; };
	void setRunning(bool value) { this->_rinning = value; };
protected:
	bool waitingTime(sf::Event event);
protected:
	bool _rinning;

	sf::Sprite* background;

	FontManager fontManager;

	sf::Clock* clock;
	sf::Time time;
};
