#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "characters.h"
#include "GameScreen.h"
#include <string>
#include <iostream>

using namespace std;

class PumpingScreen : public GameScreen
{
public:
	PumpingScreen();
	void render(vector<characters> heroes, sf::RenderWindow* window, int gameScore) override;
	void update(sf::Event event, vector<characters> &heroes, int& gameScore) override;
private:
	int currentSetting;
	bool setting;
	const int settingCount = 4;

	int currentHero;

	sf::Sprite* arrow;
	
	float colorValue;
	bool increase;
	float offset;
};