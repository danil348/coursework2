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
	void send(vector<characters>& enemyHeroes, vector<characters>& heroes, bool send);
	bool receive(vector<characters>& enemyHeroes, vector<characters>& heroes, bool& send);
	void receive(vector<characters>& enemyHeroes, vector<characters>& heroes, 
		bool& _needWalk, vector<string>& battle_events);
	void send(vector<characters>& heroes, bool& _needWalk, string battle_events, int currentHero, int currentOpponent, int damage);
	void send(string value);
	void send(bool value);
	void receive(vector<string>& battle_events, vector<characters>& heroes, vector<characters>& enemyHeroes);
	bool receive();
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

