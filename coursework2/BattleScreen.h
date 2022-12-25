#pragma once
#include <SFML/Graphics.hpp>
#include "GameScreen.h"
#include "Tcp_Socket.h"
#include <Windows.h>
#include <string>

using namespace std;

class BattleScreen : public GameScreen
{
public:
	BattleScreen();
	void render(vector<characters> heroes, sf::RenderWindow* window, int gameScore) override;
	void update(sf::Event event, vector<characters>& heroes, int& gameScore) override;
	
	void renderStrokeTable(sf::RenderWindow* window);
	void renderHero(sf::RenderWindow* window, vector<characters>& heroes);
private:
	void keyPressed(string& value);

	sf::Time _time;
	sf::Clock* _clock;
	bool _waitingTime(sf::Event event, int time);

	int currentItem;
	const int menuItemsCount = 2;

	sf::Sprite* soc_background;
	enum { server, client, undefined } soc_type;
	enum { type_selection, data_entry, connection, game } soc_connect_step;
	enum { nothing_received, heroes_received, actions_received } receiving_stage;
	string soc_ip;
	unsigned short soc_port;
	string _soc_port;
	Tcp_Socket* soc_tcp;

	HWND name;
	vector<characters> enemyHeroes;

	bool _needWalk;

	sf::RectangleShape* playerTime;
	sf::RectangleShape* enemyTime;
	const int WalkTime = 15;
};