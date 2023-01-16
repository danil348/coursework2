#include "PumpingScreen.h"

PumpingScreen::PumpingScreen()
{
	this->clock = new sf::Clock;
	this->currentHero = 0;
	this->background = TextureManager::load("img/PumpingScreen.png", 1920, 1080);
	this->arrow = TextureManager::load("img/bol.png", 30, 30);
	this->colorValue = 75;
	this->increase = true;
	this->offset = 150;
	this->currentSetting = 0;
	this->setting = false;
	this->_rinning = false;
}

void PumpingScreen::render(vector<characters>& heroes, sf::RenderWindow* window, int& gameScore)
{
	for (int i = 0; i < heroes.size(); i++) {
		heroes[i].set_w_h(1000, 900);
	}

	window->draw(*this->background);
	window->draw(*heroes[this->currentHero].getSprite()); 
	window->draw(*this->fontManager.getText(heroes[currentHero].name, 50,
		heroes[this->currentHero].getSelected() == true ? sf::Color::Red : sf::Color::Black, 1200, 100));

	for (int i = 0; i < this->ITEM_COUNT; i++) {
		window->draw(*this->fontManager.getText(this->pumpingItems[i], 30,
			this->setting == true && this->currentSetting == i ? sf::Color::Red : sf::Color::Black
			, 1000, 200 + this->offset * i));

		window->draw(*this->fontManager.getText(to_string(heroes[this->currentHero].getCharacteristic(i)), 30, 
			sf::Color::Black, 1000 + 350, 200 + this->offset * i));
	}

	window->draw(*this->fontManager.getText(L"Очки: ", 30, sf::Color::Black, 20, 20));
	window->draw(*this->fontManager.getText(to_string(gameScore), 30, sf::Color::Black, 100, 20));

	window->draw(*this->fontManager.getText(this->helpingItems[heroes[this->currentHero].getSelected()], 30, sf::Color(this->colorValue, this->colorValue, this->colorValue), 580, 1000));
}

void PumpingScreen::update(sf::Event event, vector<characters> &heroes, int& gameScore)
{
	if (this->waitingTime(event) == true) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
		{
			this->clock->restart();
			heroes[this->currentHero].setSelected(false);
			this->currentHero--;

			this->setting = false;
			this->currentSetting = 0;

			if (this->currentHero < 0) 
			{
				this->currentHero = heroes.size() - 1;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			this->clock->restart();
			heroes[this->currentHero].setSelected(false);
			this->currentHero++;

			this->setting = false;
			this->currentSetting = 0;
			
			if (this->currentHero > heroes.size() - 1) {
				this->currentHero = 0;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			this->clock->restart();
			heroes[this->currentHero].setSelected(true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			this->_rinning = false;
		}

		for (int i = 0; i < heroes.size(); i++) {
			if (heroes[i].getSelected() == true) {
				this->setting = true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					this->clock->restart();
					this->currentSetting++;
					if (this->currentSetting > this->settingCount) {
						this->currentSetting = 0;
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					this->clock->restart();
					this->currentSetting--;
					if (this->currentSetting < 0) {
						this->currentSetting = this->settingCount;
					}
				}
			}
		}

		if (heroes[this->currentHero].getSelected() == true && this->setting == true && gameScore > 0 && 
			sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) 
		{
			this->clock->restart();

			if (heroes[this->currentHero].getCharacteristic(this->currentSetting) < 100) {
				heroes[this->currentHero].getCharacteristic(this->currentSetting)++;
				gameScore--;
			}
		}
	}

	if (this->colorValue < 30) {
		this->increase = true;
	}
	else if (this->colorValue > 100) {
		this->increase = false;
	}

	if (this->increase == false) {
		this->colorValue -= 0.5;
	}
	else {
		this->colorValue += 0.5;
	}
}

bool PumpingScreen::waitingTime(sf::Event event)
{
	if (event.type == sf::Event::KeyReleased) {
		this->time = sf::seconds(2);
	}
	this->time = this->clock->getElapsedTime();
	return (this->time.asMilliseconds() >= 200);
}