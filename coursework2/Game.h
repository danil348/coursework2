#pragma once
#include <SFML/Graphics.hpp>
#include "Tcp_Socket.h"
#include "GameScreen.h"
#include "characters.h"
#include "PumpingScreen.h"
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
	PumpingScreen pumpingScreen;
	
	GameScreen screen;
};

