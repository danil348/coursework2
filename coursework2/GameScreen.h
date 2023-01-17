#pragma once
#include <SFML/Graphics.hpp>
#include "characters.h" 
#include "FontManager.h"

using namespace std;

class GameScreen
{
public:
	virtual void render(vector<characters>& heroes, sf::RenderWindow* window, int& gameScore) = 0;
	virtual void update(sf::Event event, vector<characters>& heroes, int& gameScore) = 0;
	virtual bool waitingTime(sf::Event event) = 0;
protected:
	bool _rinning;

	FontManager fontManager;

	sf::Sprite* background;
	sf::Clock* clock;
	sf::Time time;
};
