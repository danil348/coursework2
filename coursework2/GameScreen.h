#pragma once
#include "GameScreen.h"
#include "Tcp_Socket.h"
#include <Windows.h>
#include <string>
#include <vector>
#include "Field.h"
#include "Ship.h"

using namespace std;

class Screen
{
public:
	virtual void render() = 0;
	virtual void update() = 0;
protected:
	bool _rinning;
};


class GameScreen : public Screen
{
public:
	GameScreen();
	void render() override;
	void update() override;
	void renderField();
	void renderEnemyField();
	
	void fill();
	void autoFill();
	void manualFill();
	bool canPlaceShip(const Ship& ship);

	void winsUpdate();

	bool isRunning() { return this->_rinning; };
	void setRunning(bool value) { this->_rinning = value; };

	int gameSize = 12;

	bool needSend = false;
	bool needWalk = false;
	bool needRender = true;
	bool gameEnd = false;
	bool zeroWins = false;
	Field* dataSend;
	Field* dataReceive;
	
	vector<Ship> ships;
	vector<Ship> enemyShips;
private:
	void restart();

	vector<vector<Field*>> fieldsItems;
};