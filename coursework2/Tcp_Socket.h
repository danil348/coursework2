#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include "characters.h"

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
	void send(vector<characters>& enemyHeroes, vector<characters>& heroes);
	void receive(vector<characters>& enemyHeroes, vector<characters>& heroes);
	void receive(vector<characters>& enemyHeroes, vector<characters>& heroes, 
		bool& _needWalk, vector<string>& battle_events);
	void send(vector<characters>& heroes, bool& _needWalk, string battle_events);
	void send(string value);
	void receive(vector<string>& battle_events);
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

