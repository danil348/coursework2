#include "PumpingScreen.h"

PumpingScreen::PumpingScreen()
{
	this->clock = new sf::Clock;
	this->currentHero = 0;
	this->background = TextureManager::load("img/PumpingScreen.png", 1920, 1080);
	this->arrow = TextureManager::load("img/bol.jpg", 100, 100, sf::Color(255, 255, 255));
	this->colorValue = 75;
	this->increase = true;
	this->offset = 50;
}

void PumpingScreen::render(vector<characters> heroes, sf::RenderWindow* window, int gameScore)
{
	
	window->draw(*this->background);
	window->draw(*heroes[this->currentHero].getSprite()); 
	window->draw(*this->fontManager.getText(heroes[currentHero].getName(), 50,
		heroes[this->currentHero].getSelected() == true ? sf::Color::Red : sf::Color::Black, 1200, 100));

	window->draw(*this->fontManager.getText(L"Àòàêà: ", 30, sf::Color::Black, 1000, 200));
	window->draw(*this->fontManager.getText(to_string(heroes[this->currentHero].getAttack()), 30, sf::Color::Black, 1000 + 350, 200));

	window->draw(*this->fontManager.getText(L"Áðîíÿ: ", 30, sf::Color::Black, 1000, 200 + this->offset * 1));
	window->draw(*this->fontManager.getText(to_string(heroes[this->currentHero].getArmor()), 30, sf::Color::Black, 1000 + 350, 200 + this->offset * 1));

	window->draw(*this->fontManager.getText(L"Çäîðîâüå: ", 30, sf::Color::Black, 1000, 200 + this->offset * 2));
	window->draw(*this->fontManager.getText(to_string(heroes[this->currentHero].getHealth()), 30, sf::Color::Black, 1000 + 350, 200 + this->offset * 2));

	window->draw(*this->fontManager.getText(L"êðèò óðîí: ", 30, sf::Color::Black, 1000, 200 + this->offset * 3));
	window->draw(*this->fontManager.getText(to_string(heroes[this->currentHero].getCriticalDamage()), 30, sf::Color::Black, 1000 + 350, 200 + this->offset * 3));

	window->draw(*this->fontManager.getText(L"øàíñ êðèò óðîíà: ", 30, sf::Color::Black, 1000, 200 + this->offset * 4));
	window->draw(*this->fontManager.getText(to_string(heroes[this->currentHero].getCriticalDamageÑhance()), 30, sf::Color::Black, 1000 + 350, 200 + this->offset * 4));

	window->draw(*this->fontManager.getText(L"Î÷êè: ", 30, sf::Color::Black, 20, 20));
	window->draw(*this->fontManager.getText(to_string(gameScore), 30, sf::Color::Black, 100, 20));

	window->draw(*this->fontManager.getText(L"Íàæìèòå Enter, ÷òîáû íà÷àòü óëó÷øàòü ãåðîÿ", 30, sf::Color(this->colorValue, this->colorValue, this->colorValue), 580, 1000));

	window->draw(*this->arrow);
}

void PumpingScreen::update(sf::Event event, vector<characters> &heroes)
{
	this->time = this->clock->getElapsedTime();
	if (this->time.asMilliseconds() >= 250) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			heroes[this->currentHero].setSelected(false);
			this->currentHero--;
			if (this->currentHero < 0) {
				this->currentHero = heroes.size() - 1;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			heroes[this->currentHero].setSelected(false);
			this->currentHero++;
			if (this->currentHero > heroes.size() - 1) {
				this->currentHero = 0;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			heroes[this->currentHero].setSelected(true);
		}
		this->clock->restart();
	}

	if (event.type == sf::Event::KeyReleased) {
		this->time = sf::seconds(1);
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

	if (heroes[this->currentHero].getSelected() == true) {
		if (this->offset < 150) {
			this->offset += 0.5;
		}
	}
	else {
		if (this->offset > 50) {
			this->offset -= 0.5;
		}
	}
}
