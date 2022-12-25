#include "Game.h"

Game::Game()
{
	this->gameScore = 10;
	this->loadFromFile();

	this->menuIsOpen = true;
	this->menu.setRunning(true);

	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "coursework");
	//window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "coursework", sf::Style::Fullscreen);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);

	//init items
	// 
	//init items
	this->menu.setRunning(true);
}

Game::~Game()
{
	this->saveToFile();
	delete this->window;

	//delete items
	// 
	//delete items
}

void Game::gameRun()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

void Game::update()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed) {
			this->window->close();
		}
	}

	if (this->menu.isRunning() == true) {
		this->pumpingScreen.setRunning(false);
		this->battleScreen.setRunning(false);
		
		this->menu.update(this->event);
		if (this->menu.getCurrentItem() == 0 && this->menu.isRunning() == false) {
			this->pumpingScreen.setRunning(true);
		}
		if (this->menu.getCurrentItem() == 1 && this->menu.isRunning() == false) {
			this->battleScreen.setRunning(true);
		}
	}

	if (this->pumpingScreen.isRunning() == true) {
		this->menu.setRunning(false);
		this->battleScreen.setRunning(false);

		this->pumpingScreen.update(this->event, this->heroes, this->gameScore);
		if (this->pumpingScreen.isRunning() == false) {
			this->menu.setRunning(true);
		}
	}

	if (this->battleScreen.isRunning() == true) {
		this->menu.setRunning(false);
		this->pumpingScreen.setRunning(false);

		this->battleScreen.update(this->event, this->heroes, this->gameScore);
		if (this->battleScreen.isRunning() == false) {
			this->menu.setRunning(true);
		}
	}
}

void Game::render()
{
	this->window->clear();

	if (this->menu.isRunning() == true) {
		this->menu.render(this->window);
	}
	if (this->pumpingScreen.isRunning() == true) {
		this->pumpingScreen.render(this->heroes, this->window, this->gameScore);
	}
	if (this->battleScreen.isRunning() == true) {
		this->battleScreen.render(this->heroes, this->window, this->gameScore);
	}

	this->window->display();
}

void Game::loadFromFile()
{
	characters* tmpCharacters;
	ifstream file("data/data.txt");
	string tmpS;
	int tmpI;

	if (file.is_open() == true) {
		while (!file.eof())
		{
			tmpCharacters = new characters;
			file >> tmpS;
			tmpCharacters->setName(tmpS);
			file >> tmpS;
			tmpCharacters->setPicturePath(tmpS);
			tmpCharacters->setSprite();
			file >> tmpI;
			tmpCharacters->set_w_h(tmpI, tmpI);
			file >> tmpI;
			tmpCharacters->set_x(tmpI);
			file >> tmpI;
			tmpCharacters->set_y(tmpI);

			file >> tmpCharacters->armor;
			file >> tmpCharacters->attack;
			file >> tmpCharacters->health;
			file >> tmpCharacters->criticalDamage;
			file >> tmpCharacters->criticalDamageÑhance;

			this->heroes.push_back(*tmpCharacters);
		}
	}
	file.close();
}

void Game::saveToFile()
{
	ofstream file("data/data.txt");
	if (file.is_open() == true) {
		for (int i = 0; i < this->heroes.size(); i++) {
			cout << i;
			file << heroes[i].name << " ";
			file << heroes[i].picturePath << " ";
			file << heroes[i].get_h() << " ";
			file << heroes[i].get_x() << " ";
			file << heroes[i].get_y() << " ";
			file << heroes[i].armor << " ";
			file << heroes[i].attack << " ";
			file << heroes[i].health << " ";
			file << heroes[i].criticalDamage << " ";
			file << heroes[i].criticalDamageÑhance;

			if (i < this->heroes.size() - 1) {
				file << " ";
				file << endl;
			}
		}
	}
	file.close();
}
