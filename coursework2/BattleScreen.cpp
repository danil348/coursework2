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
	this->characteristicsField = new sf::RectangleShape(sf::Vector2f(300, 120));
	this->characteristicsField->setFillColor(sf::Color(255, 255, 255, 230));
	this->characteristicsFieldOpponent = new sf::RectangleShape(sf::Vector2f(150, 80));
	this->characteristicsFieldOpponent->setFillColor(sf::Color(255, 255, 255, 230));
	this->attackField = new sf::RectangleShape(sf::Vector2f(300, 160));
	this->attackField->setFillColor(sf::Color(255, 255, 255, 230));
	this->attackField->setPosition(80, 80);
	this->currentHero = 0;
	this->step_knowledge = this->step_not_received;
	this->currentDamage = 0;
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
		window->draw(*this->fontManager.getText(this->soc_ip, 50, sf::Color::Black, 30, 400));
		window->draw(*this->fontManager.getText(this->_soc_port, 50, sf::Color::Black, 30, 500));
	}



	//=============
	if (this->soc_connect_step == this->game && this->receiving_stage == this->nothing_received) {
		while (this->soc_tcp->receive(this->enemyHeroes, heroes) == false);
		this->receiving_stage = this->heroes_received;
	}
	//=============

	if (this->soc_connect_step == this->game && this->receiving_stage == this->heroes_received) {
		this->renderStrokeTable(window);
		this->renderHero(window, heroes);
		this->renderEvents(window);
	}

	if (this->soc_connect_step == this->game && this->receiving_stage == this->hit) {

	}
}

void BattleScreen::update(sf::Event event, vector<characters>& heroes, int& gameScore)
{
	if (this->soc_connect_step == this->connection && this->soc_tcp != NULL) {
		this->soc_tcp->start();
		this->soc_connect_step = this->game;
		this->_clock->restart();
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
			if (this->waitingTime(event) == true && this->step == this->character_selection) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					this->clock->restart();
					this->currentHero++;
					if (this->currentHero > heroes.size() - 1) {
						this->currentHero = 0;
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					this->clock->restart();
					this->currentHero--;
					if (this->currentHero < 0) {
						this->currentHero = heroes.size() - 1;
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && heroes[this->currentHero].islive == true) {
					this->clock->restart();
					this->step = this->choosing_opponent;
				}
			}

			if (this->waitingTime(event) == true && this->step == this->choosing_opponent) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					this->clock->restart();
					this->currentOpponent++;
					if (this->currentOpponent > this->enemyHeroes.size() - 1) {
						this->currentOpponent = 0;
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					this->clock->restart();
					this->currentOpponent--;
					if (this->currentOpponent < 0) {
						this->currentOpponent = this->enemyHeroes.size() - 1;
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && this->enemyHeroes[this->currentOpponent].islive == true) {
					this->clock->restart();
					this->step = this->hit;
				}
			}

			if (this->waitingTime(event) == true && this->step == this->hit) {
				this->heroeshit(heroes);
				this->soc_tcp->send((heroes[this->currentHero].name + " hit " + this->enemyHeroes[this->currentOpponent].name +
					" (-" + to_string(this->attackValue) + "hp)"));
				this->step = this->hit_made;
			}
		}




		if (this->_needWalk == true && this->soc_connect_step == this->game) {
			if (this->_waitingTime(event, this->WalkTime) == true) {
				cout << "send" << endl;
				if (this->step == this->hit_made) {
					if (heroes[this->currentHero].islive == true && this->enemyHeroes[this->currentOpponent].islive == true) {
						if (rand() % 101 < heroes[this->currentHero].criticalDamageÑhance) {
							this->currentDamage = heroes[this->currentHero].criticalDamage;
						}
						else {
							this->currentDamage = heroes[this->currentHero].attack;
						}

						heroes[this->currentHero].health -= this->enemyHeroes[this->currentOpponent].attack;
						heroes[this->currentHero].checkLive();
						this->enemyHeroes[this->currentOpponent].health -= this->currentDamage;
						this->enemyHeroes[this->currentOpponent].checkLive();
					}



					this->soc_tcp->send(heroes, this->_needWalk, (heroes[this->currentHero].name + " hit " + this->enemyHeroes[this->currentOpponent].name +
						" (-" + to_string(this->currentDamage) + "hp)"), this->currentHero, this->currentOpponent, this->currentDamage);
				}
				else {
					if (this->battle_events.size() > 5) {
						this->battle_events.erase(this->battle_events.begin());
					}
					this->battle_events.push_back("player: the step is skipped");
					this->soc_tcp->send(heroes, this->_needWalk, "the step is skipped", -1, -1, -1);
				}
				this->_needWalk = false;
				this->_time = sf::seconds(0);
				this->_clock->restart();
			}
		}
		else if(this->_needWalk == false && this->soc_connect_step == this->game) {
			if (this->_waitingTime(event, this->WalkTime + 0.05)) {
				cout << "receive" << endl;
				this->soc_tcp->receive(this->enemyHeroes, heroes, this->_needWalk, this->battle_events);
			}

			if (this->_needWalk == true) {
				this->_time = sf::seconds(0);
				this->_clock->restart();
				this->step = this->character_selection;
				this->currentOpponent = 0;
				this->currentHero = 0;
			}
		}
	}
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

bool BattleScreen::_waitingTime(sf::Event event, float time)
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

		if (i == this->currentHero) {
			this->characteristicsField->setPosition(heroes[i].get_x() + 10, heroes[i].get_y() - 100);
			window->draw(*this->characteristicsField);

			window->draw(*this->fontManager.getText("Armor: " + to_string(heroes[i].armor), 16, sf::Color::Black, heroes[i].get_x() + 20, heroes[i].get_y() - 90));
			window->draw(*this->fontManager.getText("Attack: " + to_string(heroes[i].attack), 16, sf::Color::Black, heroes[i].get_x() + 20, heroes[i].get_y() - 70));
			window->draw(*this->fontManager.getText("CriticalDamage: " + to_string(heroes[i].criticalDamage), 16, sf::Color::Black, heroes[i].get_x() + 20, heroes[i].get_y() - 50));
			window->draw(*this->fontManager.getText("CriticalDamageChance: " + to_string(heroes[i].criticalDamageÑhance), 16, sf::Color::Black, heroes[i].get_x() + 20, heroes[i].get_y() - 30));
			window->draw(*this->fontManager.getText("Health: " + to_string(heroes[i].health), 16, sf::Color::Black, heroes[i].get_x() + 20, heroes[i].get_y() - 10));
		}
	}
	for (int i = 0; i < enemyHeroes.size(); i++) {
		enemyHeroes[i].set_w_h(200, 200);
		enemyHeroes[i].set_x(1520 - 200 * i);
		enemyHeroes[i].set_y(800);
		window->draw(*enemyHeroes[i].getSprite());
		window->draw(*this->fontManager.getText(enemyHeroes[i].name, 16, sf::Color::Black, enemyHeroes[i].get_x() + 70, enemyHeroes[i].get_y() + 150));

		this->characteristicsFieldOpponent->setPosition(enemyHeroes[i].get_x() + 10, enemyHeroes[i].get_y() - 60);
		if (i == this->currentOpponent) {
			this->characteristicsFieldOpponent->setOutlineThickness(3);
			this->characteristicsFieldOpponent->setOutlineColor(sf::Color(0, 0, 0));
		}
		window->draw(*this->characteristicsFieldOpponent);
		this->characteristicsFieldOpponent->setOutlineThickness(0);

		window->draw(*this->fontManager.getText("Armor: " + to_string(enemyHeroes[i].armor), 16, sf::Color::Black, enemyHeroes[i].get_x() + 20, enemyHeroes[i].get_y() - 50));
		window->draw(*this->fontManager.getText("Attack: " + to_string(enemyHeroes[i].attack), 16, sf::Color::Black, enemyHeroes[i].get_x() + 20, enemyHeroes[i].get_y() - 30));
		window->draw(*this->fontManager.getText("Health: " + to_string(enemyHeroes[i].health), 16, sf::Color::Black, enemyHeroes[i].get_x() + 20, enemyHeroes[i].get_y() - 10));

		
	}
}

void BattleScreen::heroeshit(vector<characters>& heroes)
{
	if (this->battle_events.size() > 5) {
		this->battle_events.erase(this->battle_events.begin());
	}
	this->battle_events.push_back("player: " + heroes[this->currentHero].name + " hit " + this->enemyHeroes[this->currentOpponent].name +
		" (-" + to_string(this->attackValue) + "hp)");
}

void BattleScreen::renderEvents(sf::RenderWindow* window)
{
	window->draw(*this->attackField);

	for (int i = 0; i < this->battle_events.size(); i++) {
		if (this->battle_events[i][0] == 'e') {
			window->draw(*this->fontManager.getText(this->battle_events[i], 16, sf::Color::Red, 100, 100 + 20 * i));
		}
		else {
			window->draw(*this->fontManager.getText(this->battle_events[i], 16, sf::Color::Black, 100, 100 + 20 * i));
		}
	}
}
