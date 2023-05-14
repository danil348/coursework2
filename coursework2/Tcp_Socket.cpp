#include "Tcp_Socket.h"


Tcp_Socket::Tcp_Socket()
{
	this->socket.setBlocking(false);
	this->TcpType = this->server;

	this->listener.listen(sf::Socket::AnyPort);
	this->ip = new sf::IpAddress(sf::IpAddress::getLocalAddress());
	this->port = this->listener.getLocalPort();
}

Tcp_Socket::Tcp_Socket(string ip, unsigned short port)
{
	this->socket.setBlocking(false);
	this->TcpType = this->client;

	this->ip = new sf::IpAddress(ip);
	this->port = port;
}

void Tcp_Socket::start()
{
	if (this->TcpType == this->server) {
		while (this->accept() == false);
#ifdef DEBUG
		cout << endl << "подключено (это сервер)" << endl;
#endif // DEBUG
	}
	else if (this->TcpType == this->client) {
		while (this->connect() == false);

#ifdef DEBUG
		cout << endl << "подключено (это клиент)" << endl;
#endif // DEBUG
	}
}

bool Tcp_Socket::accept()
{
	return this->listener.accept(this->socket) == sf::Socket::Done;
}

bool Tcp_Socket::connect()
{
	return this->socket.connect(*this->ip, this->port) != sf::Socket::Done;
}

unsigned short Tcp_Socket::getPort()
{
	return this->port;
}

string Tcp_Socket::getIp()
{
	return this->ip->toString();
}

Field* Tcp_Socket::receive()
{
	Field* data = new Field;
	if (this->socket.receive(this->packet) == sf::Socket::Done) {
		this->packet >> data->isOccupied;
		this->packet >> data->isZero;
		this->packet >> data->x;
		this->packet >> data->y;
		return data;
	}
	return NULL;
}

void Tcp_Socket::send(Field* data)
{
	this->packet.clear();

	this->packet << data->isOccupied;
	this->packet << data->isZero;
	this->packet << data->x;
	this->packet << data->y;

	this->socket.send(this->packet);
}
