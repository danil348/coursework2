#include "Game.h"

Game::Game()
{
	this->loadFromFile();
#ifdef SOCKET
	this->socketRun();
#endif // SOCKET

	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "coursework");
	//window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "coursework", sf::Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);

	//init items
	// 
	//init items
}

Game::~Game()
{
	delete this->window;

	//delete items
	// 
	//delete items
}

void Game::gameRun()
{
	while (this->window->isOpen())
	{
		this->update();
#ifdef SOCKET
		this->sendData();
#endif // SOCKET
		this->render();
	}
}

void Game::update()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed) {
			this->window->close();
		}
	}

	this->pumpingScreen.update(this->event, this->heroes);
	//update game
	// 
	//update game
}

void Game::render()
{
	this->window->clear();

	//this->screen.render(this->window);
	this->pumpingScreen.render(heroes, window);

	//render smf
	// 
	//render smf

	this->window->display();
}

void Game::sendData()
{
	this->tcp_socket->send();
	this->tcp_socket->receive();
}

void Game::socketRun()
{
	char type;
	cout << "введите тип подключения: s - server, c - client" << endl;
	do
	{
		cin >> type;
		if (type != 'c' && type != 's') {
			cout << "повторите попытку";
		}
	} while (type != 'c' && type != 's');

	if (type == 's') {
		this->tcp_socket = new Tcp_Socket;
		cout << "ip: " << this->tcp_socket->getIp() << endl;
		cout << "port: " << this->tcp_socket->getPort();
	}
	if (type == 'c') {
		string tmpIp;
		unsigned short port;
		cout << "enter server ip: ";
		cin >> tmpIp;
		cout << "enter port: ";
		cin >> port;
		this->tcp_socket = new Tcp_Socket(tmpIp, port);
	}

	this->tcp_socket->start();
}

void Game::loadFromFile()
{
	characters* tmpCharacters;
	ifstream file("data/data.txt");
	string tmpS;
	int tmpI;

	if (file.is_open() == true) {
		while (!file.eof())
		{
			tmpCharacters = new characters;
			file >> tmpS;
			tmpCharacters->setName(tmpS);
			file >> tmpS;
			tmpCharacters->setPicturePath(tmpS);
			tmpCharacters->setSprite();
			file >> tmpI;
			tmpCharacters->set_w_h(tmpI, tmpI);
			file >> tmpI;
			tmpCharacters->set_x(tmpI);
			file >> tmpI;
			tmpCharacters->set_y(tmpI);

			this->heroes.push_back(*tmpCharacters);
		}
	}
}

void Game::saveToFile()
{
	ofstream file("data/data.txt");
	if (file.is_open() == true) {
		for (int i = 0; i < this->heroes.size(); i++) {
			file << heroes[i].getName() << " ";
			file << heroes[i].getPicturePath() << " ";
			file << heroes[i].get_h() << " ";
			file << heroes[i].get_x() << " ";
			file << heroes[i].get_y();
			if (i < this->heroes.size() - 1) {
				cout << endl;
			}
		}
	}
}
