#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <vector> // Added for vector<Ship>
#include "Field.h"
#include "Ship.h"
#include <sstream>
#include "DataReceive.h"

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
	
	DataReceive* receive();
	string receiveShipsData(vector<Ship>& enemyShips);
	
	void send(DataReceive* data);
	void sendShipsData(const vector<Ship>& ships); // Новый метод для отправки данных о кораблях
	
	void parseShipsData(const string& data, vector<Ship>& enemyShips); // Новый метод для парсинга данных о кораблях

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

