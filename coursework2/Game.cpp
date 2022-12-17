#include "Game.h"

Game::Game()
{
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

	//update game
	// 
	//update game
}

void Game::render()
{
	this->window->clear();

	this->screen.render(this->window);
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
