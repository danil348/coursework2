#include "GameScreen.h"

GameScreen::GameScreen() {
	this->zeroWinsScreen = TextureManager::load("img/5.png", 900, 900);
	this->crossWinsScreen = TextureManager::load("img/6.png", 900, 900);
	this->cross = TextureManager::load("img/1.png", 300, 300);
	this->zero = TextureManager::load("img/2.png", 300, 300);
	this->fieldBlocked = TextureManager::load("img/3.png", 300, 300);
	this->fieldAllowed = TextureManager::load("img/4.png", 300, 300);
	this->clock = new sf::Clock;
	this->_clock = new sf::Clock;

	for (int i = 0; i < 3; i++)
	{
		vector<Field*> tmp;
		for (int j = 0; j < 3; j++)
		{
			tmp.push_back(new Field(false, false));
		}
		fieldsItems.push_back(tmp);
		tmp.clear();
	}

	this->restart();
}

void GameScreen::render(sf::RenderWindow* window)
{
	if (this->gameEnd == false) {
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (this->needWalk == false) {
					this->fieldBlocked->setPosition(300 * j, 300 * i);
					window->draw(*(this->fieldBlocked));
				}
				else {
					this->fieldAllowed->setPosition(300 * j, 300 * i);
					window->draw(*(this->fieldAllowed));
				}

				if (this->fieldsItems[i][j]->isOccupied == true) {
					if (this->fieldsItems[i][j]->isZero == true) {
						this->zero->setPosition(300 * j, 300 * i);
						window->draw(*(this->zero));
					}
					else {
						this->cross->setPosition(300 * j, 300 * i);
						window->draw(*(this->cross));
					}
				}
			}
		}
	}
	else {
		if (this->zeroWins == true) {
			this->zeroWinsScreen->setPosition(0, 0);
			window->draw(*(this->zeroWinsScreen));
		}
		else {
			this->crossWinsScreen->setPosition(0, 0);
			window->draw(*(this->crossWinsScreen));
		}
	}
}

void GameScreen::update(sf::RenderWindow* window, sf::Event event)
{
	static bool lock_click;
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left && lock_click != true && this->needWalk == true)
		{
			sf::Vector2i pos = sf::Mouse::getPosition(*window);

			if (this->playerType == this->zero_type && this->fieldsItems[pos.y / 300][pos.x / 300]->isOccupied == false) {
				this->fieldsItems[pos.y / 300][pos.x / 300]->isOccupied = true;
				this->fieldsItems[pos.y / 300][pos.x / 300]->isZero = true;

				this->needSend = true;
				this->dataSend = new Field;
				this->dataSend->isOccupied = true;
				this->dataSend->isZero = true;
				this->dataSend->x = pos.x / 300;
				this->dataSend->y = pos.y / 300;
			}

			if (this->playerType == this->cross_type && this->fieldsItems[pos.y / 300][pos.x / 300]->isOccupied == false) {
				this->fieldsItems[pos.y / 300][pos.x / 300]->isOccupied = true;
				this->fieldsItems[pos.y / 300][pos.x / 300]->isZero = false;

				this->needSend = true;
				this->dataSend = new Field;
				this->dataSend->isOccupied = true;
				this->dataSend->isZero = false;
				this->dataSend->x = pos.x / 300;
				this->dataSend->y = pos.y / 300;
			}

			lock_click = true;
		}
	}

	if (this->dataReceive) {
		this->fieldsItems[this->dataReceive->y][this->dataReceive->x]->isOccupied = this->dataReceive->isOccupied;
		this->fieldsItems[this->dataReceive->y][this->dataReceive->x]->isZero = this->dataReceive->isZero;
		this->fieldsItems[this->dataReceive->y][this->dataReceive->x]->x = this->dataReceive->x;
		this->fieldsItems[this->dataReceive->y][this->dataReceive->x]->y = this->dataReceive->y;
		this->dataReceive = NULL;
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			lock_click = false;
		}
	}
}

void GameScreen::winsUpdate()
{
	if (((this->fieldsItems[0][0]->isZero && this->fieldsItems[0][0]->isOccupied) == true && (this->fieldsItems[0][1]->isZero && this->fieldsItems[0][1]->isOccupied) == true && (this->fieldsItems[0][2]->isZero && this->fieldsItems[0][2]->isOccupied) == true) ||
		((this->fieldsItems[1][0]->isZero && this->fieldsItems[1][0]->isOccupied) == true && (this->fieldsItems[1][1]->isZero && this->fieldsItems[1][1]->isOccupied) == true && (this->fieldsItems[1][2]->isZero && this->fieldsItems[1][2]->isOccupied) == true) ||
		((this->fieldsItems[2][0]->isZero && this->fieldsItems[2][0]->isOccupied) == true && (this->fieldsItems[2][1]->isZero && this->fieldsItems[2][1]->isOccupied) == true && (this->fieldsItems[2][2]->isZero && this->fieldsItems[2][2]->isOccupied) == true) ||
		((this->fieldsItems[0][0]->isZero && this->fieldsItems[0][0]->isOccupied) == true && (this->fieldsItems[1][0]->isZero && this->fieldsItems[1][0]->isOccupied) == true && (this->fieldsItems[2][0]->isZero && this->fieldsItems[2][0]->isOccupied) == true) ||
		((this->fieldsItems[0][1]->isZero && this->fieldsItems[0][1]->isOccupied) == true && (this->fieldsItems[1][1]->isZero && this->fieldsItems[1][1]->isOccupied) == true && (this->fieldsItems[2][1]->isZero && this->fieldsItems[2][1]->isOccupied) == true) ||
		((this->fieldsItems[0][2]->isZero && this->fieldsItems[0][2]->isOccupied) == true && (this->fieldsItems[1][2]->isZero && this->fieldsItems[1][2]->isOccupied) == true && (this->fieldsItems[2][2]->isZero && this->fieldsItems[2][2]->isOccupied) == true) ||
		((this->fieldsItems[0][0]->isZero && this->fieldsItems[0][0]->isOccupied) == true && (this->fieldsItems[1][1]->isZero && this->fieldsItems[1][1]->isOccupied) == true && (this->fieldsItems[2][2]->isZero && this->fieldsItems[2][2]->isOccupied) == true) ||
		((this->fieldsItems[2][0]->isZero && this->fieldsItems[2][0]->isOccupied) == true && (this->fieldsItems[1][1]->isZero && this->fieldsItems[1][1]->isOccupied) == true && (this->fieldsItems[0][2]->isZero && this->fieldsItems[0][2]->isOccupied) == true)) {
		this->needWalk = false;
		this->gameEnd = true;
		this->zeroWins = true;
	}
	else if (
		(this->fieldsItems[0][0]->isZero == false && this->fieldsItems[0][0]->isOccupied == true && this->fieldsItems[0][1]->isZero == false && this->fieldsItems[0][1]->isOccupied == true && this->fieldsItems[0][2]->isZero == false && this->fieldsItems[0][2]->isOccupied == true) ||
		(this->fieldsItems[1][0]->isZero == false && this->fieldsItems[1][0]->isOccupied == true && this->fieldsItems[1][1]->isZero == false && this->fieldsItems[1][1]->isOccupied == true && this->fieldsItems[1][2]->isZero == false && this->fieldsItems[1][2]->isOccupied == true) ||
		(this->fieldsItems[2][0]->isZero == false && this->fieldsItems[2][0]->isOccupied == true && this->fieldsItems[2][1]->isZero == false && this->fieldsItems[2][1]->isOccupied == true && this->fieldsItems[2][2]->isZero == false && this->fieldsItems[2][2]->isOccupied == true) ||
		(this->fieldsItems[0][0]->isZero == false && this->fieldsItems[0][0]->isOccupied == true && this->fieldsItems[1][0]->isZero == false && this->fieldsItems[1][0]->isOccupied == true && this->fieldsItems[2][0]->isZero == false && this->fieldsItems[2][0]->isOccupied == true) ||
		(this->fieldsItems[0][1]->isZero == false && this->fieldsItems[0][1]->isOccupied == true && this->fieldsItems[1][1]->isZero == false && this->fieldsItems[1][1]->isOccupied == true && this->fieldsItems[2][1]->isZero == false && this->fieldsItems[2][1]->isOccupied == true) ||
		(this->fieldsItems[0][2]->isZero == false && this->fieldsItems[0][2]->isOccupied == true && this->fieldsItems[1][2]->isZero == false && this->fieldsItems[1][2]->isOccupied == true && this->fieldsItems[2][2]->isZero == false && this->fieldsItems[2][2]->isOccupied == true) ||
		(this->fieldsItems[0][0]->isZero == false && this->fieldsItems[0][0]->isOccupied == true && this->fieldsItems[1][1]->isZero == false && this->fieldsItems[1][1]->isOccupied == true && this->fieldsItems[2][2]->isZero == false && this->fieldsItems[2][2]->isOccupied == true) ||
		(this->fieldsItems[2][0]->isZero == false && this->fieldsItems[2][0]->isOccupied == true && this->fieldsItems[1][1]->isZero == false && this->fieldsItems[1][1]->isOccupied == true && this->fieldsItems[0][2]->isZero == false && this->fieldsItems[0][2]->isOccupied == true)) {
		this->needWalk = false;
		this->gameEnd = true;
		this->zeroWins = false;
	}
}

void GameScreen::keyPressed(string& value, sf::Event event)
{
	for (int i = sf::Keyboard::Num0; i <= sf::Keyboard::Num9; i++) {
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i))) {
			this->clock->restart();
			value += to_string(i - 26);
			break;
		}
	}
}

void GameScreen::restart()
{
	this->clock->restart();
	this->_clock->restart();
	this->time = sf::microseconds(0);
	this->_time = sf::microseconds(0);
	this->_rinning = false;
	this->currentItem = 0;
	this->dataReceive = NULL;
}

