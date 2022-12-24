#include "GameScreen.h"

bool GameScreen::waitingTime(sf::Event event)
{
	if (event.type == sf::Event::KeyReleased) {
		this->time = sf::seconds(2);
	}
	this->time = this->clock->getElapsedTime();
	return (this->time.asMilliseconds() >= 200);
}