#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "FontManager.h"
#include "Setting.h"

using namespace std;

class Menu
{
public:
	Menu();
	void render(sf::RenderWindow* window);
	void update(sf::Event event, sf::RenderWindow* window);
	bool waitingTime(sf::Event event);
	bool isRunning() { return this->_isRunning; };
	void setRunning(bool value) { this->_isRunning = value; };
	int getCurrentItem() { return this->currentItem; };
private:
	bool _isRunning;
	int currentItem;

	FontManager fontM;
	sf::Sprite* background;

	sf::Clock* clock;
	sf::Time time;

	wstring menuItems[3] = { L"Прокачка",L"битва",L"Настройки" };
	const int ITEMS_COUNT = 3;
	const int ITEMS_COUNT_SETTING = 2;


	enum { setting_menu, main_menu } menu;
};