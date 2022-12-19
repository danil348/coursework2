#include "GameScreen.h"

GameScreen::GameScreen()
{
	this->background = TextureManager::load("img/arena.jpg", 1920, 1080);
}

void GameScreen::render(sf::RenderWindow* window)
{
	window->draw(*this->background);
}
