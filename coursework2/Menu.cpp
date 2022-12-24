#include "Menu.h"

Menu::Menu()
{
	this->background = TextureManager::load("img/PumpingScreen.png", 1920, 1080);
	this->currentItem = 0;
	this->clock = new sf::Clock;
	this->_isRunning = false;
}

void Menu::render(sf::RenderWindow* window)
{
	window->draw(*this->background);
	window->draw(*this->fontM.getText(L"Прокачка", 50,
		this->currentItem == 0 ? sf::Color::Red : sf::Color::Black
		, 30, 400));

	window->draw(*this->fontM.getText(L"Битва", 50,
		this->currentItem == 1 ? sf::Color::Red : sf::Color::Black
		, 30, 500));

	window->draw(*this->fontM.getText(L"Настройки", 50,
		this->currentItem == 2 ? sf::Color::Red : sf::Color::Black
		, 30, 600));
}

void Menu::update(sf::Event event)
{
	if (this->waitingTime(event) == true) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			this->clock->restart();
			this->currentItem++;
			if (this->currentItem > this->menuItemsCount - 1) {
				this->currentItem = 0;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			this->clock->restart();
			this->currentItem--;
			if (this->currentItem < 0) {
				this->currentItem = this->menuItemsCount - 1;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			this->_isRunning = false;
		}
	}
}

bool Menu::waitingTime(sf::Event event)
{
	if (event.type == sf::Event::KeyReleased) {
		this->time = sf::seconds(2);
	}
	this->time = this->clock->getElapsedTime();
	return (this->time.asMilliseconds() >= 200);
}