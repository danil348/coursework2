#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include "Field.h"

#define DEBUG

using namespace std;

class Tcp_Socket
{
public:
	Tcp_Socket();
	Tcp_Socket(string ip, unsigned short port);
public:
	void start();
	bool accept();
	bool connect();
	Field* receive();
	void send(Field* data);
public:
	unsigned short getPort();
	string getIp();
private:
	sf::TcpSocket socket;
	sf::IpAddress* ip;
	sf::TcpListener listener;
	sf::Packet packet;
	
	unsigned short port;

	enum { server , client} TcpType;
};

