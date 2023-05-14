#pragma once
#include "FontManager.h"
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "GameScreen.h"
#include "Tcp_Socket.h"
#include <Windows.h>
#include <string>
#include <vector>
#include "Field.h"

using namespace std;

class Screen
{
public:
	virtual void render(sf::RenderWindow* window) = 0;
	virtual void update(sf::RenderWindow* window, sf::Event event) = 0;
protected:
	bool _rinning;

	FontManager fontManager;
	
	sf::Clock* clock;
	sf::Time time;
};


class GameScreen : public Screen
{
public:
	GameScreen();
	void render(sf::RenderWindow* window) override;
	void update(sf::RenderWindow* window, sf::Event event) override;

	void winsUpdate();

	bool isRunning() { return this->_rinning; };
	void setRunning(bool value) { this->_rinning = value; };

	int playerType;
	enum playerTypes { cross_type, zero_type };

	bool needSend = false;
	bool needWalk = false;
	bool gameEnd = false;
	bool zeroWins = false;
	Field* dataSend;
	Field* dataReceive;
private:
	void restart();
	void keyPressed(string& value, sf::Event event);

	sf::Time _time;
	sf::Clock* _clock;

	int currentItem;

	vector<vector<Field*>> fieldsItems;

	sf::Sprite* fieldBlocked;
	sf::Sprite* fieldAllowed;
	sf::Sprite* cross;
	sf::Sprite* zero;
	sf::Sprite* zeroWinsScreen;
	sf::Sprite* crossWinsScreen;
};