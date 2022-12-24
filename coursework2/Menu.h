#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "FontManager.h"

using namespace std;

class Menu
{
public:
	Menu();
	void render(sf::RenderWindow* window);
	void update(sf::Event event);
	bool waitingTime(sf::Event event);
	bool isRunning() { return this->_isRunning; };
	void setRunning(bool value) { this->_isRunning = value; };
	int getCurrentItem() { return this->currentItem; };
private:
	bool _isRunning;
	int currentItem;
	const int menuItemsCount = 3;

	FontManager fontM;
	sf::Sprite* background;

	sf::Clock* clock;
	sf::Time time;
};