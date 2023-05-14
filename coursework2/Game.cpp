#include "Game.h"
#define SOCKET

Game::Game()
{
#ifdef SOCKET
	this->socketRun();
#endif // SOCKET

	this->window = new sf::RenderWindow(sf::VideoMode(900, 900), "coursework");
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);


	this->gameScreen.setRunning(true);
}

Game::~Game()
{
	delete this->window;
}

void Game::gameRun()
{
	while (this->window->isOpen())
	{
		this->update();

		Field* tmp;
		tmp = this->tcp_socket->receive();
		if (tmp) {
			this->gameScreen.dataReceive = new Field;
			this->gameScreen.dataReceive->isOccupied = tmp->isOccupied;
			this->gameScreen.dataReceive->isZero = tmp->isZero;
			this->gameScreen.dataReceive->y = tmp->y;
			this->gameScreen.dataReceive->x = tmp->x;

			this->gameScreen.needWalk = true;
		}
		delete tmp;

		this->gameScreen.winsUpdate();

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

	if (this->gameScreen.isRunning() == true) {
		this->gameScreen.update(this->window, this->event);

		if (this->gameScreen.needSend == true) {
			this->tcp_socket->send(this->gameScreen.dataSend);
			this->gameScreen.needSend = false;
			this->gameScreen.needWalk = false;
		}
	}
}

void Game::render()
{
	this->window->clear();

	if (this->gameScreen.isRunning() == true) {
		this->gameScreen.render(this->window);
	}

	this->window->display();
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
		this->gameScreen.playerType = this->gameScreen.cross_type;
		this->gameScreen.needWalk = true;

		this->tcp_socket = new Tcp_Socket;
		cout << "ip: " << this->tcp_socket->getIp() << endl;
		cout << "port: " << this->tcp_socket->getPort();
	}
	if (type == 'c') {
		this->gameScreen.playerType = this->gameScreen.zero_type;
		this->gameScreen.needWalk = false;

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
