#pragma once
#include <SFML/Graphics.hpp>
#include "characters.h" 
#include "FontManager.h"

using namespace std;

class GameScreen
{
public:
	virtual void render(vector<characters>& heroes, sf::RenderWindow* window, int& gameScore) {};
	virtual void update(sf::Event event, vector<characters>& heroes, int& gameScore) {};
protected:
	bool _rinning;

	FontManager fontManager;

	sf::Sprite* background;
	sf::Clock* clock;
	sf::Time time;
};
