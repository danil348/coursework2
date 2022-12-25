#include "BattleScreen.h"

BattleScreen::BattleScreen() 
{
	this->clock = new sf::Clock;
	this->_clock = new sf::Clock;
	this->background = TextureManager::load("img/arena.jpg", 1920, 1080);
	this->soc_background = TextureManager::load("img/PumpingScreen.png", 1920, 1080);
	this->_rinning = false;
	this->soc_ip = "Ip: ";
	this->_soc_port = "Port: ";
	this->soc_port = 0;
	this->currentItem = 0;
	this->soc_type = this->undefined;
	this->soc_connect_step = this->type_selection;
	this->soc_tcp = NULL;
	this->name = NULL;
	this->receiving_stage = this->nothing_received;
	this->_needWalk = false;
	this->playerTime = new sf::RectangleShape(sf::Vector2f(100, 30));
	this->playerTime->setPosition(760, 1000);
	this->enemyTime = new sf::RectangleShape(sf::Vector2f(100, 30));
	this->enemyTime->setPosition(1060, 1000);
}

void BattleScreen::render(vector<characters> heroes, sf::RenderWindow* window, int gameScore)
{
	window->draw(*(this->soc_connect_step == this->type_selection || 
		this->soc_connect_step == this->data_entry ||
		this->soc_connect_step == this->connection ? this->soc_background : this->background));

	if (this->soc_connect_step == this->type_selection) {
		window->draw(*this->fontManager.getText(L"Êëèåíò", 50,
			this->currentItem == 0 ? sf::Color::Red : sf::Color::Black
			, 30, 400));

		window->draw(*this->fontManager.getText(L"Ñåðâåð", 50,
			this->currentItem == 1 ? sf::Color::Red : sf::Color::Black
			, 30, 500));
	}

	if ((this->soc_connect_step == this->connection || this->soc_connect_step == this->data_entry) && this->soc_type == this->server) {
		cout << this->soc_ip;
		window->draw(*this->fontManager.getText(this->soc_ip, 30, sf::Color::Black, 100, 800));
		window->draw(*this->fontManager.getText(this->_soc_port, 30, sf::Color::Black, 100, 900));
	}

	if (this->soc_connect_step == this->data_entry && this->soc_type == this->client) {
		window->draw(*this->fontManager.getText(this->soc_ip, 50, sf::Color::Black , 30, 400));
		window->draw(*this->fontManager.getText(this->_soc_port, 50, sf::Color::Black , 30, 500));
	}



	//=============
	if (this->soc_connect_step == this->game && this->receiving_stage != this->heroes_received) {
		this->soc_tcp->receive(this->enemyHeroes, heroes);
		this->receiving_stage = this->heroes_received;
	}
	//=============
	
	if (this->soc_connect_step == this->game && this->receiving_stage == this->heroes_received) {
		this->renderStrokeTable(window);
		this->renderHero(window, heroes);
	}
}

void BattleScreen::update(sf::Event event, vector<characters>& heroes, int& gameScore)
{
	if (this->soc_connect_step == this->connection && this->soc_tcp != NULL) {
		this->soc_tcp->start();
		this->soc_connect_step = this->game;
		if (this->soc_type == this->server) {
			this->_needWalk = true;
			this->clock->restart();
		}
	}



	//=============
	if (this->soc_connect_step == this->game && this->receiving_stage != this->heroes_received) {
		this->soc_tcp->send(this->enemyHeroes, heroes);
	}
	//=============

	
	
	
	if (this->name == NULL) {
		this->name = GetForegroundWindow();
	}

	if (this->waitingTime(event) == true && this->name == GetForegroundWindow()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			this->clock->restart();
			this->_rinning = false;
			this->soc_connect_step = this->type_selection;
			this->soc_tcp = NULL;
			this->soc_type = this->undefined;
			this->receiving_stage = this->nothing_received;
			this->soc_ip = "Ip: ";
			this->soc_port = NULL;
			this->_soc_port = "Port: ";
			this->enemyHeroes.clear();
		}
	}

	if (this->waitingTime(event) == true && this->name == GetForegroundWindow() && this->soc_connect_step != this->game) {
		if (this->soc_connect_step == this->type_selection) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				this->clock->restart();
				this->clock->restart();
				this->currentItem++;
				if (this->currentItem > this->menuItemsCount - 1) {
					this->currentItem = 0;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				this->clock->restart();
				this->clock->restart();
				this->currentItem--;
				if (this->currentItem < 0) {
					this->currentItem = this->menuItemsCount - 1;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				this->clock->restart();
				this->soc_connect_step = this->data_entry;
				if (this->currentItem == 0) {
					this->soc_type = this->client;
				}
				else {
					this->soc_type = this->server;
				}
			}
		}
		else if (this->soc_connect_step == this->data_entry) {
			if (this->soc_type == this->server) {
				if (this->soc_tcp == NULL) {
					this->soc_tcp = new Tcp_Socket;
					this->soc_ip = "Ip: " + this->soc_tcp->getIp();
					this->_soc_port = "Port: " + to_string(this->soc_tcp->getPort());
					this->soc_connect_step = this->connection;
				}
			}
			if (this->soc_type == this->client) {
				if (this->soc_tcp == NULL) {
					if (this->soc_ip.size() < 17) {
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma)) {
							this->clock->restart();
							this->soc_ip += ".";
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
							this->clock->restart();
							if (this->soc_ip.size() > 4) {
								this->soc_ip = this->soc_ip.substr(0, this->soc_ip.size() - 1);
							}
						}
						this->keyPressed(this->soc_ip);
					}
					else if (this->_soc_port.size() < 11) {
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
							this->clock->restart();
							if (this->_soc_port.size() > 6) {
								this->_soc_port = this->_soc_port.substr(0, this->_soc_port.size() - 1);
							}
						}
						this->keyPressed(this->_soc_port);
					}

					if (this->soc_ip.size() >= 13 && this->_soc_port.size() >= 5 && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
						this->soc_tcp = new Tcp_Socket(this->soc_ip.substr(4,this->soc_ip.size()), unsigned short(atoi(this->_soc_port.substr(6, this->_soc_port.size()).c_str())));
						this->soc_connect_step = this->connection;
					}
				}
			}
			
		}
	}


	if (this->receiving_stage == this->heroes_received && this->soc_connect_step == this->game) {
		if (this->_needWalk == true) {
			if (this->_waitingTime(event, this->WalkTime) == true) {
				this->soc_tcp->send(heroes, this->_needWalk);
				this->_needWalk = false;
				this->_time = sf::seconds(0);
				this->_clock->restart();
			}
		}
		else {
			this->_waitingTime(event, this->WalkTime);
			this->soc_tcp->receive(this->enemyHeroes, heroes, this->_needWalk);
			if (this->_needWalk == true) {
				this->_time = sf::seconds(0);
				this->_clock->restart();
			}
		}
	}

	//=============
	/*if (this->receiving_stage == this->heroes_received) {
		for (int i = 0; i < enemyHeroes.size(); i++) {
			cout << enemyHeroes[i].name << endl;
			cout << enemyHeroes[i].get_h() << endl;
			cout << enemyHeroes[i].get_w() << endl;
			cout << enemyHeroes[i].armor << endl;
			cout << enemyHeroes[i].attack << endl;
			cout << enemyHeroes[i].criticalDamage << endl;
			cout << enemyHeroes[i].criticalDamageÑhance << endl;
			cout << enemyHeroes[i].health << endl;
			cout << enemyHeroes[i].name << endl;
			cout << enemyHeroes[i].picturePath << endl << endl;
		}
	}*/
	//=============
}

void BattleScreen::keyPressed(string& value) 
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
		this->clock->restart();
		value += "0";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		this->clock->restart();
		value += "1";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		this->clock->restart();
		value += "2";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
		this->clock->restart();
		value += "3";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
		this->clock->restart();
		value += "4";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
		this->clock->restart();
		value += "5";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
		this->clock->restart();
		value += "6";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
		this->clock->restart();
		value += "7";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
		this->clock->restart();
		value += "8";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
		this->clock->restart();
		value += "9";
	}
	
}

bool BattleScreen::_waitingTime(sf::Event event, int time)
{
	this->_time = this->_clock->getElapsedTime();
	return (this->_time.asSeconds() >= time);
}

void BattleScreen::renderStrokeTable(sf::RenderWindow* window) 
{
	if (this->_needWalk == true) {
		this->playerTime->setFillColor(sf::Color(0, 0, 255, 255));
		this->enemyTime->setFillColor(sf::Color(255, 0, 0, 75));
	}
	else {
		this->playerTime->setFillColor(sf::Color(0, 0, 255, 75));
		this->enemyTime->setFillColor(sf::Color(255, 0, 0, 255));
	}

	window->draw(*this->fontManager.getText(to_string(this->WalkTime - int(this->_time.asSeconds())), 30, sf::Color::Black, 950, 1000));
	window->draw(*this->playerTime);
	window->draw(*this->enemyTime);
}

void BattleScreen::renderHero(sf::RenderWindow* window, vector<characters>& heroes)
{
	for (int i = 0; i < heroes.size(); i++) {
		heroes[i].set_w_h(200, 200);
		heroes[i].set_x(200 + 200 * i);
		heroes[i].set_y(800);
		window->draw(*heroes[i].getSprite());
		window->draw(*this->fontManager.getText(heroes[i].name, 16, sf::Color::Black, heroes[i].get_x() + 70, heroes[i].get_y() + 150));
	}
	for (int i = 0; i < enemyHeroes.size(); i++) {
		enemyHeroes[i].set_w_h(200, 200);
		enemyHeroes[i].set_x(1520 - 200 * i);
		enemyHeroes[i].set_y(800);
		window->draw(*enemyHeroes[i].getSprite());
		window->draw(*this->fontManager.getText(enemyHeroes[i].name, 16, sf::Color::Black, enemyHeroes[i].get_x() + 70, enemyHeroes[i].get_y() + 150));
	}
}