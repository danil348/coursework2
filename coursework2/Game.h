#pragma once
#include <SFML/Graphics.hpp>
#include "Tcp_Socket.h"
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

private:
	sf::RenderWindow* window;
	sf::Event event;
	Tcp_Socket* tcp_socket;
};

