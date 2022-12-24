#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "FontManager.h"
#include "characters.h"
#include <string>
#include <iostream>

using namespace std;

class PumpingScreen
{
public:
	PumpingScreen();
	void render(vector<characters> heroes, sf::RenderWindow* window, int gameScore);
	void update(sf::Event event, vector<characters> &heroes, int& gameScore);
private:
	int currentSetting;
	bool setting;
	const int settingCount = 4;

	int currentHero;
	FontManager fontManager;

	sf::Sprite* background;
	sf::Sprite* arrow;
	
	sf::Clock* clock;
	sf::Time time;

	float colorValue;
	bool increase;
	float offset;
};