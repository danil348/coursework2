#pragma once
#include <SFML/Network.hpp>
#include <iostream>

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
	void send();
	void receive();
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

