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

void PumpingScreen::render(vector<characters> heroes, sf::RenderWindow* window, int gameScore)
{
	
	window->draw(*this->background);
	window->draw(*heroes[this->currentHero].getSprite()); 
	window->draw(*this->fontManager.getText(heroes[currentHero].name, 50,
		heroes[this->currentHero].getSelected() == true ? sf::Color::Red : sf::Color::Black, 1200, 100));

	window->draw(*this->fontManager.getText(L"¿Ú‡Í‡: ", 30,
		this->setting == true && this->currentSetting == 0 ? sf::Color::Red : sf::Color::Black
		, 1000, 200));

	window->draw(*this->fontManager.getText(to_string(heroes[this->currentHero].attack), 30, sf::Color::Black, 1000 + 350, 200));

	window->draw(*this->fontManager.getText(L"¡ÓÌˇ: ", 30,
		this->setting == true && this->currentSetting == 1 ? sf::Color::Red : sf::Color::Black
		, 1000, 200 + this->offset * 1));
	window->draw(*this->fontManager.getText(to_string(heroes[this->currentHero].armor), 30, sf::Color::Black, 1000 + 350, 200 + this->offset * 1));

	window->draw(*this->fontManager.getText(L"«‰ÓÓ‚¸Â: ", 30,
		this->setting == true && this->currentSetting == 2 ? sf::Color::Red : sf::Color::Black
		, 1000, 200 + this->offset * 2));
	window->draw(*this->fontManager.getText(to_string(heroes[this->currentHero].health), 30, sf::Color::Black, 1000 + 350, 200 + this->offset * 2));

	window->draw(*this->fontManager.getText(L"ÍËÚ ÛÓÌ: ", 30,
		this->setting == true && this->currentSetting == 3 ? sf::Color::Red : sf::Color::Black
		, 1000, 200 + this->offset * 3));
	window->draw(*this->fontManager.getText(to_string(heroes[this->currentHero].criticalDamage), 30, sf::Color::Black, 1000 + 350, 200 + this->offset * 3));

	window->draw(*this->fontManager.getText(L"¯‡ÌÒ ÍËÚ ÛÓÌ‡: ", 30,
		this->setting == true && this->currentSetting == 4 ? sf::Color::Red : sf::Color::Black
	, 1000, 200 + this->offset * 4));
	window->draw(*this->fontManager.getText(to_string(heroes[this->currentHero].criticalDamage—hance), 30, sf::Color::Black, 1000 + 350, 200 + this->offset * 4));

	window->draw(*this->fontManager.getText(L"Œ˜ÍË: ", 30, sf::Color::Black, 20, 20));
	window->draw(*this->fontManager.getText(to_string(gameScore), 30, sf::Color::Black, 100, 20));

	if (heroes[this->currentHero].getSelected() == false) {
		window->draw(*this->fontManager.getText(L"Õ‡ÊÏËÚÂ Enter, ˜ÚÓ·˚ Ì‡˜‡Ú¸ ÛÎÛ˜¯‡Ú¸ „ÂÓˇ", 30, sf::Color(this->colorValue, this->colorValue, this->colorValue), 580, 1000));
	}
	else {
		window->draw(*this->fontManager.getText(L"Õ‡ÊÏËÚÂ RCntrl, ˜ÚÓ·˚ Û‚ÂÎË˜ËÚ¸ ‚˚·‡ÌÌÛ˛ ı‡‡ÍÚÂËÒÚËÍÛ", 30, sf::Color(this->colorValue, this->colorValue, this->colorValue), 510, 1000));
	}
	
	//window->draw(*this->arrow);
}

void PumpingScreen::update(sf::Event event, vector<characters> &heroes, int& gameScore)
{
	if (this->waitingTime(event) == true) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			this->clock->restart();
			heroes[this->currentHero].setSelected(false);
			this->currentHero--;

			this->setting = false;
			this->currentSetting = 0;

			if (this->currentHero < 0) {
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
			sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
			this->clock->restart();
			if (this->currentSetting == 0 && heroes[this->currentHero].attack < 100) {
				gameScore--;
				heroes[this->currentHero].attack++;
			}
			else if (this->currentSetting == 1 && heroes[this->currentHero].armor < 100) {
				gameScore--;
				heroes[this->currentHero].armor++;
			}
			else if (this->currentSetting == 2 && heroes[this->currentHero].health < 100) {
				gameScore--;
				heroes[this->currentHero].health++;
			}
			else if (this->currentSetting == 3 && heroes[this->currentHero].criticalDamage < 100) {
				gameScore--;
				heroes[this->currentHero].criticalDamage++;
			}
			else if (this->currentSetting == 4 && heroes[this->currentHero].criticalDamage—hance < 100) {
				gameScore--;
				heroes[this->currentHero].criticalDamage—hance++;
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
