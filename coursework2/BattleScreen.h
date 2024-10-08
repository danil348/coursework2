#pragma once
#include <SFML/Graphics.hpp>
#include "GameScreen.h"
#include "Tcp_Socket.h"
#include "Music.h"
#include <Windows.h>
#include <string>

using namespace std;

class BattleScreen : public GameScreen
{
public:
	BattleScreen();
	void render(vector<characters>& heroes, sf::RenderWindow* window, int& gameScore) override;
	void update(sf::Event event, vector<characters>& heroes, int& gameScore) override;
	bool waitingTime(sf::Event event) override;
	
	void renderStrokeTable(sf::RenderWindow* window);
	void renderHero(sf::RenderWindow* window, vector<characters>& heroes); 
	void heroeshit(vector<characters>& heroes);
	void renderEvents(sf::RenderWindow* window);

	bool isRunning() { return this->_rinning; };
	void setRunning(bool value) { this->_rinning = value; };


	MusicManager* music;
private:
	string getHitString(characters hero);
	void restart();
	void keyPressed(string& value, sf::Event event);
	bool fightOver(vector<characters>& heroes);

	sf::Time _time;
	sf::Clock* _clock;
	bool _waitingTime(sf::Event event, float time);

	int currentItem;
	const int menuItemsCount = 2;

	sf::Sprite* soc_background;
	enum { server, client, undefined } soc_type;
	enum { type_selection, data_entry, connection, game, end } soc_connect_step;
	enum { nothing_received, heroes_received, actions_received } receiving_stage;
	enum { character_selection, choosing_opponent, hit, hit_made} step;
	enum { step_not_received, step_received} step_knowledge;
	enum { victory, loss } status;
	string soc_ip;
	unsigned short soc_port;
	string _soc_port;
	Tcp_Socket* soc_tcp;

	HWND name;
	vector<characters> enemyHeroes;

	bool _needWalk;

	sf::RectangleShape* playerTime;
	sf::RectangleShape* enemyTime;
	sf::RectangleShape* characteristicsField;
	sf::RectangleShape* characteristicsFieldOpponent;
	sf::RectangleShape* attackField;
	const int WalkTime = 15;
	int currentHero;
	int currentOpponent;
	vector<string> battle_events;

	int attackValue;

	int currentDamage;

	bool send = false;

	bool flag = false;
};