#include "PumpingScreen.h"

PumpingScreen::PumpingScreen()
{
	this->clock = new sf::Clock;
	this->currentHero = 0;
	this->background = TextureManager::load("img/PumpingScreen.png", 1920, 1080);
}

void PumpingScreen::render(vector<characters> heroes, sf::RenderWindow* window)
{
	window->draw(*this->background);
	window->draw(*heroes[currentHero].getSprite()); 
	window->draw(*fontManager.getText(heroes[currentHero].getName(), 50, sf::Color::Black, 1200, 100));

	window->draw(*fontManager.getText("Attack: ", 30, sf::Color::Black, 1000, 200));
	window->draw(*fontManager.getText(to_string(heroes[currentHero].getAttack()), 30, sf::Color::Black, 1000 + 350, 200));

	window->draw(*fontManager.getText("Armor: ", 30, sf::Color::Black, 1000, 250));
	window->draw(*fontManager.getText(to_string(heroes[currentHero].getArmor()), 30, sf::Color::Black, 1000 + 350, 250));

}

void PumpingScreen::update(sf::Event event, vector<characters> heroes)
{
	this->time = this->clock->getElapsedTime();

	if (event.type == sf::Event::KeyPressed && this->time.asMilliseconds() >= 250) {
		if (event.key.code == sf::Keyboard::Left) {
			this->currentHero--;
			if (this->currentHero < 0) {
				this->currentHero = heroes.size() - 1;
			}
		}
		else if (event.key.code == sf::Keyboard::Right) {
			this->currentHero++;
			if (this->currentHero > heroes.size() - 1) {
				this->currentHero = 0;
			}
		}
		this->clock->restart();
	}

	if (event.type == sf::Event::KeyReleased) {
		this->time = sf::seconds(1);
	}
}
