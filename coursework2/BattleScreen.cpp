#include "BattleScreen.h"

BattleScreen::BattleScreen() 
{
	this->background = TextureManager::load("img/arena.jpg", 1920, 1080);
	this->soc_background = TextureManager::load("img/PumpingScreen.png", 1920, 1080);
	this->music = new MusicManager;
	music->music_load("music/elearning-clock-ticking.wav");
	music->music_load("music/Minecraft.wav");
	this->clock = new sf::Clock;
	this->_clock = new sf::Clock;
	this->playerTime = new sf::RectangleShape(sf::Vector2f(100, 30));
	this->enemyTime = new sf::RectangleShape(sf::Vector2f(100, 30));
	this->characteristicsField = new sf::RectangleShape(sf::Vector2f(300, 120));
	this->characteristicsFieldOpponent = new sf::RectangleShape(sf::Vector2f(150, 80));
	this->attackField = new sf::RectangleShape(sf::Vector2f(300, 160));

	this->restart();
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


	if (this->soc_type == this->server && this->soc_connect_step == this->game && this->receiving_stage == this->nothing_received) {
		while (this->soc_tcp->receive(this->enemyHeroes, heroes, this->send) == false) {
			this->soc_tcp->send(false);
		}
		this->soc_tcp->send(true);
		this->receiving_stage = this->heroes_received;
	}

	if (this->soc_type == this->client && this->soc_connect_step == this->game && this->receiving_stage == this->nothing_received) {
		while (this->soc_tcp->receive() == false) {
			this->soc_tcp->send(this->enemyHeroes, heroes, (this->receiving_stage == this->heroes_received));
		}
	}

	if (this->soc_type == this->client && this->soc_connect_step == this->game && this->receiving_stage == this->nothing_received) {
		while (this->soc_tcp->receive(this->enemyHeroes, heroes, this->send) == false) {
			this->soc_tcp->send(false);
		}
		this->soc_tcp->send(true);
		this->receiving_stage = this->heroes_received;
	}

	if (this->soc_type == this->server && this->soc_connect_step == this->game && flag == false) {
		while (this->soc_tcp->receive() == false) {
			this->soc_tcp->send(this->enemyHeroes, heroes, (this->receiving_stage == this->heroes_received));
		}
		flag = true;
	}

	//=============
	/*if (this->soc_connect_step == this->game && this->receiving_stage == this->nothing_received) {
		while (this->soc_tcp->receive(this->enemyHeroes, heroes, this->send) == false) {
		}
		this->receiving_stage = this->heroes_received;
	}*/
	//=============

	if (this->soc_connect_step == this->game && this->receiving_stage == this->heroes_received) {
		this->renderStrokeTable(window);
		this->renderHero(window, heroes);
		this->renderEvents(window);
	}
}

void BattleScreen::update(sf::Event event, vector<characters>& heroes, int& gameScore)
{
	if (this->step == this->game) {
		//
		// ===
		//
	}

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
	/*if (this->soc_connect_step == this->game && this->send == false) {
		cout << (this->receiving_stage == this->heroes_received);
		this->soc_tcp->send(this->enemyHeroes, heroes, (this->receiving_stage == this->heroes_received));
		this->soc_tcp->receive(this->enemyHeroes, heroes, this->send);
	}*/
	//=============

	
	
	
	if (this->name == NULL) {
		this->name = GetForegroundWindow();
	}

	if (this->waitingTime(event) == true && this->name == GetForegroundWindow()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			this->restart();
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
						this->keyPressed(this->soc_ip, event);
					}
					else if (this->_soc_port.size() < 11) {
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
							this->clock->restart();
							if (this->_soc_port.size() > 6) {
								this->_soc_port = this->_soc_port.substr(0, this->_soc_port.size() - 1);
							}
						}
						this->keyPressed(this->_soc_port, event);
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
			if (this->_clock->getElapsedTime().asSeconds() > 10) {
				this->music->play_music(0);
			}
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
				this->soc_tcp->send(this->getHitString(heroes[this->currentHero]));
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

					this->soc_tcp->send(heroes, this->_needWalk, this->getHitString(heroes[this->currentHero]), this->currentHero, this->currentOpponent, this->currentDamage);
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
				this->music->stop_music(0);
			}
		}
		else if(this->_needWalk == false && this->soc_connect_step == this->game) {
			if (this->_waitingTime(event, this->WalkTime)) {
				while (this->soc_tcp->receive(this->enemyHeroes, heroes, this->_needWalk, this->battle_events) == false);
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

void BattleScreen::keyPressed(string& value, sf::Event event) 
{
	for (int i = sf::Keyboard::Num0; i <= sf::Keyboard::Num9; i++) {
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i))) {
			this->clock->restart();
			value += to_string(i - 26);
			break;
		}
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

			for (int j = 0; j < heroes[i].characteristicCount; j++) {
				window->draw(*this->fontManager.getText(heroes[i].getCharacteristicName(j) + ": " + to_string(heroes[i].getCharacteristic(j))
					, 16, sf::Color::Black, heroes[i].get_x() + 20, heroes[i].get_y() - 90 + 20 * j));
			}
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

		for (int j = 0; j < enemyHeroes[i].characteristicCount; j++) {
			window->draw(*this->fontManager.getText(enemyHeroes[i].getCharacteristicName(j) + ": " + to_string(enemyHeroes[i].getCharacteristic(j))
				, 16, sf::Color::Black, enemyHeroes[i].get_x() + 20, enemyHeroes[i].get_y() - 50 + 20 * j));
		}
	}
}

void BattleScreen::heroeshit(vector<characters>& heroes)
{
	if (this->battle_events.size() > 5) {
		this->battle_events.erase(this->battle_events.begin());
	}
	this->battle_events.push_back("player: " + this->getHitString(heroes[this->currentHero]));
}

void BattleScreen::renderEvents(sf::RenderWindow* window)
{
	window->draw(*this->attackField);

	for (int i = 0; i < this->battle_events.size(); i++) {
		window->draw(*this->fontManager.getText(this->battle_events[i], 16, 
			(this->battle_events[i][0] == 'e' ? sf::Color::Red : sf::Color::Black), 
			100, 100 + 20 * i));
	}
}

void BattleScreen::restart()
{
	this->clock->restart();
	this->_clock->restart();
	this->time = sf::microseconds(0);
	this->_time = sf::microseconds(0);
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
	this->playerTime->setPosition(760, 1000);
	this->enemyTime->setPosition(1060, 1000);
	this->characteristicsField->setFillColor(sf::Color(255, 255, 255, 230));
	this->characteristicsFieldOpponent->setFillColor(sf::Color(255, 255, 255, 230));
	this->attackField->setFillColor(sf::Color(255, 255, 255, 230));
	this->attackField->setPosition(80, 80);
	this->currentHero = 0;
	this->step_knowledge = this->step_not_received;
	this->currentDamage = 0;
}


string BattleScreen::getHitString(characters hero) {
	return (hero.name + " hit " + this->enemyHeroes[this->currentOpponent].name +
		" (-" + to_string(this->currentDamage) + "hp)");
}
