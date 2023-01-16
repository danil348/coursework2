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
		cout << endl << "ïîäêëþ÷åíî (ýòî ñåðâåð)" << endl;
#endif // DEBUG
	}
	else if (this->TcpType == this->client) {
		while (this->connect() == false);

#ifdef DEBUG
		cout << endl << "ïîäêëþ÷åíî (ýòî êëèåíò)" << endl;
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

void Tcp_Socket::send(vector<characters>& enemyHeroes, vector<characters>& heroes, bool send)
{
	this->packet.clear();

	this->packet << int(heroes.size());
	for (int i = 0; i < heroes.size(); i++) {
		this->packet << heroes[i].get_h();
		this->packet << heroes[i].get_w();
		this->packet << heroes[i].armor;
		this->packet << heroes[i].attack;
		this->packet << heroes[i].criticalDamage;
		this->packet << heroes[i].criticalDamageÑhance;
		this->packet << heroes[i].health;
		this->packet << heroes[i].name;
		this->packet << heroes[i].picturePath;
	}

	this->packet << int(send);
	this->socket.send(this->packet);
}

bool Tcp_Socket::receive(vector<characters>& enemyHeroes, vector<characters>& heroes, bool& send)
{
	int count;
	int w, h;
	enemyHeroes.clear();
	characters* tmpCharacters;
	if (this->socket.receive(this->packet) == sf::Socket::Done) {
		this->packet >> count;
		for (int i = 0; i < count; i++) {
			tmpCharacters = new characters;
			this->packet >> h;
			this->packet >> w;
			tmpCharacters->set_w_h(w, h);
			this->packet >> tmpCharacters->armor;
			this->packet >> tmpCharacters->attack;
			this->packet >> tmpCharacters->criticalDamage;
			this->packet >> tmpCharacters->criticalDamageÑhance;
			this->packet >> tmpCharacters->health;
			this->packet >> tmpCharacters->name;
			this->packet >> tmpCharacters->picturePath;
			tmpCharacters->setSprite();
			enemyHeroes.push_back(*tmpCharacters);
		}

		this->packet >> count;
		send = count;
	}

	return enemyHeroes.size() != 0;
}

bool Tcp_Socket::receive(vector<characters>& enemyHeroes, vector<characters>& heroes, 
	bool& _needWalk, vector<string>& battle_events)
{
	int q;
	if (this->socket.receive(this->packet) == sf::Socket::Done) {

		this->packet >> q;
		this->packet >> _needWalk;

		if (battle_events.size() > 5) {
			battle_events.erase(battle_events.begin());
		}
		string tmp = " ";
		this->packet >> tmp;
		if (tmp != "") {
			battle_events.push_back("enemy: " + tmp);
		}

		int tmpidx = -1;
		int tmpidx2 = -1;
		int tmpidx3 = -1;
		this->packet >> tmpidx;
		this->packet >> tmpidx2;
		this->packet >> tmpidx3;

		if (tmpidx >= 0 && tmpidx2 >= 0 && tmpidx3 >= 0) {
			enemyHeroes[tmpidx].health -= heroes[tmpidx2].attack;
			heroes[tmpidx2].health -= tmpidx3;

			enemyHeroes[tmpidx].checkLive();
			heroes[tmpidx2].checkLive();
		}
	}
	return q == -1;
}

void Tcp_Socket::send(vector<characters>& heroes, bool& _needWalk, string battle_events, int currentHero, int currentOpponent, int damage)
{
	this->packet.clear();

	this->packet << -1;
	this->packet << _needWalk;
	this->packet << battle_events;
	this->packet << currentHero;
	this->packet << currentOpponent;
	this->packet << damage;

	this->socket.send(this->packet);
}

void Tcp_Socket::send(string value)
{
	this->packet.clear();

	this->packet << value;

	this->socket.send(this->packet);
}

void Tcp_Socket::send(bool value)
{
	this->packet.clear();

	this->packet << value;

	this->socket.send(this->packet);
}

void Tcp_Socket::receive(vector<string>& battle_events, vector<characters>& heroes, vector<characters>& enemyHeroes)
{
	if (this->socket.receive(this->packet) == sf::Socket::Done) {
		if (battle_events.size() > 5) {
			battle_events.erase(battle_events.begin());
		}
		string tmp;
		this->packet >> tmp;
		battle_events.push_back(tmp);
	}
}

bool Tcp_Socket::receive()
{
	bool value;
	if (this->socket.receive(this->packet) == sf::Socket::Done) {
		this->packet >> value;
		return value;
	}
	return false;
}