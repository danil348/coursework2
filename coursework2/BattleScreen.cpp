#include "BattleScreen.h"

BattleScreen::BattleScreen() 
{
	this->clock = new sf::Clock;
	this->background = TextureManager::load("img/arena.jpg", 1920, 1080);
	this->soc_background = TextureManager::load("img/PumpingScreen.png", 1920, 1080);
	this->_rinning = false;
	this->soc_ip = "ip: ";
	this->soc_port = 0;
	this->currentItem = 0;
	this->soc_type = this->undefined;
	this->soc_connect_step = this->type_selection;
	this->soc_tcp = NULL;
	this->_render = false;
}

void BattleScreen::render(vector<characters> heroes, sf::RenderWindow* window, int gameScore)
{
	window->draw(*(this->soc_connect_step == this->type_selection || this->soc_connect_step == this->data_entry ? this->soc_background : this->background));

	if (this->soc_connect_step == this->type_selection) {
		window->draw(*this->fontManager.getText(L"Клиент", 50,
			this->currentItem == 0 ? sf::Color::Red : sf::Color::Black
			, 30, 400));

		window->draw(*this->fontManager.getText(L"Сервер", 50,
			this->currentItem == 1 ? sf::Color::Red : sf::Color::Black
			, 30, 500));
	}

	if ((this->soc_connect_step == this->connection || this->soc_connect_step == this->game) && this->soc_type == this->server) {
		cout << this->soc_ip;
		window->draw(*this->fontManager.getText(this->soc_ip, 30, sf::Color::Black, 100, 800));
		window->draw(*this->fontManager.getText(this->_soc_port, 30, sf::Color::Black, 100, 900));
	}

	if (this->soc_connect_step == this->data_entry && this->soc_type == this->client) {
		window->draw(*this->fontManager.getText(this->soc_ip, 50,
			this->currentItem == 0 ? sf::Color::Red : sf::Color::Black
			, 30, 400));

		window->draw(*this->fontManager.getText(this->_soc_port, 50,
			this->currentItem == 1 ? sf::Color::Red : sf::Color::Black
			, 30, 500));
	}

}

void BattleScreen::update(sf::Event event, vector<characters>& heroes, int& gameScore)
{
	if (this->soc_connect_step == this->connection && this->_render == true && this->soc_tcp != NULL) {
		this->soc_tcp->start();
		this->soc_connect_step = this->game;
	}
	if (this->soc_connect_step == this->game) {
		this->soc_tcp->send(heroes, heroes);
		this->soc_tcp->receive(heroes, heroes);
	}

	if (this->waitingTime(event) == true) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			this->clock->restart();
			this->_rinning = false;
			this->soc_connect_step = this->type_selection;
			this->soc_tcp = NULL;
			this->soc_type = this->undefined;
		}
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
						this->keyPressed(this->soc_ip);
					}
					else if (this->_soc_port.size() < 5) {
						this->keyPressed(this->_soc_port);
						cout << atoi(this->_soc_port.c_str()) << endl;
					}

					if (this->soc_ip.size() >= 13 && this->_soc_port.size() >= 5 && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
						this->soc_tcp = new Tcp_Socket(this->soc_ip, atoi(this->_soc_port.c_str()));
						this->soc_connect_step = this->connection;
					}
				}
			}
			
		}
	}

	this->_render = true;
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