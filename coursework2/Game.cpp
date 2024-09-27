#include "Game.h"

#define SOCKET

Game::Game()
{
#ifdef SOCKET
	this->socketRun();
#endif // SOCKET

	string tmp;
	this->gameScreen.fill();

	cout << "waiting for ships data" << endl;

	try
	{
		do {
			this->tcp_socket->sendShipsData(this->gameScreen.ships);
			tmp = this->tcp_socket->receiveShipsData(this->gameScreen.enemyShips);
		} while (tmp.empty());
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
#ifdef DEBUG
	cout << "ships data received!" << endl;
	cout << tmp << endl;
#endif // DEBUG

	this->gameScreen.setRunning(true);
}

Game::~Game()
{
}

void Game::gameRun()
{
	while (true)
	{
		this->gameScreen.receiveData();
		
		this->render();
		this->update();

		DataReceive* tmp;
		tmp = this->tcp_socket->receive();
		if (tmp) {
			this->gameScreen.dataReceive = new DataReceive;
			
			this->gameScreen.dataReceive->y = tmp->y;
			this->gameScreen.dataReceive->x = tmp->x;
			this->gameScreen.dataReceive->isPlayerStep = tmp->isPlayerStep;
			
			this->gameScreen.needWalk = !tmp->isPlayerStep;
		}
		delete tmp;

		this->gameScreen.winsUpdate();

		this->render();
	}
}

void Game::update()
{
	if (this->gameScreen.isRunning() == true) {
		this->gameScreen.update();

		if (this->gameScreen.needSend == true) {
			this->tcp_socket->send(this->gameScreen.dataSend);
			this->gameScreen.needSend = false;
			this->gameScreen.needWalk = this->gameScreen.dataSend->isPlayerStep;
		}
	}
}

void Game::render()
{
	if (this->gameScreen.isRunning() == true) {
		this->gameScreen.render();
	}
}

void Game::socketRun()
{
	char type;
	cout << "Choose type: s - server, c - client" << endl;
	do
	{
		cin >> type;
		if (type != 'c' && type != 's') {
			cout << "Wrong type!" << endl;
		}
	} while (type != 'c' && type != 's');

	if (type == 's') {
		//this->gameScreen.playerType = this->gameScreen.cross_type;
		this->gameScreen.needWalk = true;

		this->tcp_socket = new Tcp_Socket;
		cout << "ip: " << this->tcp_socket->getIp() << endl;
		cout << "port: " << this->tcp_socket->getPort();
	}
	if (type == 'c') {
		//this->gameScreen.playerType = this->gameScreen.zero_type;
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
