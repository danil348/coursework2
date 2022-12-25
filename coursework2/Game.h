#pragma once
#include <SFML/Graphics.hpp>
#include "Tcp_Socket.h"
#include "characters.h"
#include "PumpingScreen.h"
#include "BattleScreen.h"
#include "GameScreen.h"
#include "Menu.h"
#include <fstream>
#include <vector>

using namespace std;

class Game
{
public:
	Game();
	~Game();

public:
	void update();
	void render();
public:
	void gameRun();
public:
	void loadFromFile();
	void saveToFile();
private:
	int gameScore;
	sf::RenderWindow* window;
	sf::Event event;

	vector<characters> heroes;
	vector<characters> enemyHeroes;

	bool pumpingScreenIsOpen;
	PumpingScreen pumpingScreen;

	bool menuIsOpen;
	Menu menu;

	bool battleScreenIsOpen;
	BattleScreen battleScreen;
};

