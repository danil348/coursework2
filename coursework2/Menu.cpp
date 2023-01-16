#include "Menu.h"

Menu::Menu()
{
	this->background = TextureManager::load("img/PumpingScreen.png", 1920, 1080);
	this->currentItem = 0;
	this->clock = new sf::Clock;
	this->_isRunning = false;
	this->menu = this->main_menu;
}

void Menu::render(sf::RenderWindow* window)
{
	window->draw(*this->background);
	switch (this->menu)
	{
	case  this->setting_menu:
		window->draw(*this->fontM.getText(L"«вуки", 50, this->currentItem == 0 ? sf::Color::Red : sf::Color::Black, 30, 400));
		window->draw(*this->fontM.getText(Setting::sound == true ? L"вкл" : L"выкл", 50, sf::Color::Black, 200, 400));

		window->draw(*this->fontM.getText(L"Ёкран", 50, this->currentItem == 1 ? sf::Color::Red : sf::Color::Black, 30, 500));
		window->draw(*this->fontM.getText(to_string(Setting::screenWidth) + "X" + to_string(Setting::screenHeight), 50, sf::Color::Black, 200, 500));
		break;
	case  this->main_menu:
		for (int i = 0; i < this->ITEMS_COUNT; i++) {
			window->draw(*this->fontM.getText(menuItems[i], 50,
				this->currentItem == i ? sf::Color::Red : sf::Color::Black
				, 30, 400 + 100 * i));
		}
		break;
	default:
		break;
	}
}

void Menu::update(sf::Event event, sf::RenderWindow* window)
{
	if (this->waitingTime(event) == true) {
		switch (this->menu)
		{
		case  this->setting_menu:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				this->clock->restart();
				this->currentItem++;
				if (this->currentItem > this->ITEMS_COUNT_SETTING - 1) {
					this->currentItem = 0;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				this->clock->restart();
				this->currentItem--;
				if (this->currentItem < 0) {
					this->currentItem = this->ITEMS_COUNT_SETTING - 1;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				cout << "asd";
				this->clock->restart();
				if (this->currentItem == 0) {
					Setting::sound = !Setting::sound;
				}
				else if (this->currentItem == 1) {
					Setting::next();
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				this->clock->restart();
				if (this->currentItem == 0) {
					Setting::sound = !Setting::sound;
				}
				else if (this->currentItem == 1) {
					Setting::prev();
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				this->clock->restart();
				this->menu = this->main_menu;
				this->currentItem = 0;
				window->create(sf::VideoMode(Setting::screenWidth, Setting::screenHeight), "coursework", sf::Style::Default);
				window->setFramerateLimit(144);
				window->setVerticalSyncEnabled(false);
			}
			break;
		case  this->main_menu:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				this->clock->restart();
				this->currentItem++;
				if (this->currentItem > this->ITEMS_COUNT - 1) {
					this->currentItem = 0;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				this->clock->restart();
				this->currentItem--;
				if (this->currentItem < 0) {
					this->currentItem = this->ITEMS_COUNT - 1;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				if (this->currentItem == 1 || this->currentItem == 0) {
					this->clock->restart();
					this->_isRunning = false;
				}
				else {
					this->clock->restart();
					this->currentItem = 0;
					this->menu = this->setting_menu;
				}
			}
			break;
		default:
			break;
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