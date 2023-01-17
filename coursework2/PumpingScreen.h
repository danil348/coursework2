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
	void render(vector<characters>& heroes, sf::RenderWindow* window, int& gameScore) override;
	void update(sf::Event event, vector<characters> &heroes, int& gameScore) override;
	bool waitingTime(sf::Event event) override;

	bool isRunning() { return this->_rinning; };
	void setRunning(bool value) { this->_rinning = value; };

private:
	int currentSetting;
	bool setting;
	const int settingCount = 4;

	int currentHero;

	sf::Sprite* arrow;
	
	float colorValue;
	bool increase;
	float offset;

	wstring pumpingItems[6] = { L"Атака: " , L"Броня: " ,L"Здоровье: " ,L"крит урон: " ,L"шанс крит урона: ",L"Очки: " };
	const int ITEM_COUNT = 6;

	wstring helpingItems[2] = { L"Нажмите Enter, чтобы начать улучшать героя" , L"Нажмите RCntrl, чтобы увеличить выбранную характеристику" };
	const int H_ITEM_COUNT = 2;
};

/*
	window->draw(*this->background);
	window->draw(*heroes[this->currentHero].getSprite()); 
	window->draw(*this->fontManager.getText(heroes[currentHero].name, 50,
		heroes[this->currentHero].getSelected() == true ? sf::Color::Red : sf::Color::Black, 1200, 100));

	for (int i = 0; i < this->ITEM_COUNT; i++) {
		window->draw(*this->fontManager.getText(this->pumpingItems[i], 30,
			this->setting == true && this->currentSetting == i ? sf::Color::Red : sf::Color::Black
			, 1000, 200 + this->offset * i));
	}

	window->draw(*this->fontManager.getText(this->helpingItems[heroes[this->currentHero].getSelected()], 30, sf::Color(this->colorValue, this->colorValue, this->colorValue), 580, 1000));
*/