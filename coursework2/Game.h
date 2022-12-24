#pragma once
#include <SFML/Graphics.hpp>
#include "Tcp_Socket.h"
#include "characters.h"
#include "PumpingScreen.h"
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
	void sendData();
public:
	void gameRun();
	void socketRun();
public:
	void loadFromFile();
	void saveToFile();
private:
	int gameScore;
	sf::RenderWindow* window;
	sf::Event event;
	Tcp_Socket* tcp_socket;

	vector<characters> heroes;
	vector<characters> enemyHeroes;

	bool pumpingScreenIsOpen;
	PumpingScreen pumpingScreen;

	bool menuIsOpen;
	Menu menu;
};

