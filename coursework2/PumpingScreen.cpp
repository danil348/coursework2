#include "PumpingScreen.h"

PumpingScreen::PumpingScreen()
{
	this->currentHero = 0;
	this->background = TextureManager::load("img/PumpingScreen.png", 1920, 1080);
}

void PumpingScreen::render(vector<characters> heroes, sf::RenderWindow* window)
{
	window->draw(*this->background);
	window->draw(*heroes[currentHero].getSprite());
}

void PumpingScreen::update(sf::Event event, vector<characters> heroes)
{
	if (event.type == sf::Event::KeyPressed) {
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
	}
}
