#pragma once
#include <SFML/Graphics.hpp>
#include "GameScreen.h"
#include "Tcp_Socket.h"
#include <string>

using namespace std;

class BattleScreen : public GameScreen
{
public:
	BattleScreen();
	void render(vector<characters> heroes, sf::RenderWindow* window, int gameScore) override;
	void update(sf::Event event, vector<characters>& heroes, int& gameScore) override;
private:
	void keyPressed(string& value);

	int currentItem;
	const int menuItemsCount = 2;

	sf::Sprite* soc_background;
	enum { server, client, undefined } soc_type;
	enum { type_selection, data_entry, connection, game } soc_connect_step;
	string soc_ip;
	unsigned short soc_port;
	string _soc_port;
	Tcp_Socket* soc_tcp;
};