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
		cout << endl << "Server connected" << endl;
#endif // DEBUG
	}
	else if (this->TcpType == this->client) {
		while (this->connect() == false);
#ifdef DEBUG
		cout << endl << "Client connected" << endl;
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

DataReceive* Tcp_Socket::receive()
{
	if (this->socket.receive(this->packet) == sf::Socket::Done) {
		DataReceive* data = new DataReceive;


		this->packet >> data->x;
		this->packet >> data->y;
		this->packet >> data->isPlayerStep;

		if(data->x > 12 || data->y > 12){
			return NULL;
		}

		return data;
	}
	return NULL;
}

string Tcp_Socket::receiveShipsData(vector<Ship>& enemyShips) {
	if (this->socket.receive(this->packet) == sf::Socket::Done) {
		string data;
		this->packet >> data;
		this->parseShipsData(data, enemyShips);
		return data;
	}
	return "";
}

void Tcp_Socket::send(DataReceive* data)
{
	this->packet.clear();

	this->packet << data->x;
	this->packet << data->y;
	this->packet << data->isPlayerStep;

	this->socket.send(this->packet);
}

void Tcp_Socket::sendShipsData(const vector<Ship>& ships) {
	this->packet.clear(); // Очистка пакета перед отправкой

	string data = "";

	for (const Ship& ship : ships) {
		int size = ship.getPositions().size(); // Получаем размер корабля
		bool isHorizontal = ship.getOrientation(); // Получаем ориентацию корабля

		// Форматируем данные
		data += "s:" + to_string(size) + ",o:" + (isHorizontal ? "h" : "v") + 
				",x:" + to_string(ship.getPositions().front().x) + 
				",y:" + to_string(ship.getPositions().front().y) + ";";
	}

	// Удаляем последний символ ';' если он есть
	if (!data.empty()) {
		data.pop_back();
	}

	this->packet << data; // Добавляем сериализованные данные в пакет
	this->socket.send(this->packet); // Отправка всего пакета
}

void Tcp_Socket::parseShipsData(const string& data, vector<Ship>& enemyShips) {
    size_t start = 0;
    size_t end = data.find(';');

    while (end != string::npos) {
        string shipData = data.substr(start, end - start); // Извлекаем данные о корабле
        Ship ship;

        // Парсинг данных о корабле
        int size = 0;
        char orientation = ' ';
        int x = 0, y = 0;

        // Извлечение параметров из строки
        size_t sPos = shipData.find("s:") + 2;
        size_t oPos = shipData.find("o:") + 2;
        size_t xPos = shipData.find("x:") + 2;
        size_t yPos = shipData.find("y:") + 2;

        // Получаем размер
        size = stoi(shipData.substr(sPos, shipData.find(',', sPos) - sPos));
        // Получаем ориентацию
        orientation = shipData[oPos];
        // Получаем координаты
        x = stoi(shipData.substr(xPos, shipData.find(',', xPos) - xPos));
        y = stoi(shipData.substr(yPos, shipData.find(';', yPos) - yPos));

        // Устанавливаем параметры корабля
        ship.setSize(size);
        ship.setOrientation(orientation == 'h'); // Преобразуем символ в булевое значение
        ship.setPosition(x, y); // Устанавливаем позицию

        enemyShips.push_back(ship); // Добавляем корабль в вектор

        start = end + 1; // Переход к следующему кораблю
        end = data.find(';', start); // Находим следующий разделитель
    }

    // Обработка последнего корабля, если он есть
    if (start < data.length()) {
        string shipData = data.substr(start); // Извлекаем данные о последнем корабле
        Ship ship;

        // Парсинг данных о корабле
        int size = 0;
        char orientation = ' ';
        int x = 0, y = 0;

        // Извлечение параметров из строки
        size_t sPos = shipData.find("s:") + 2;
        size_t oPos = shipData.find("o:") + 2;
        size_t xPos = shipData.find("x:") + 2;
        size_t yPos = shipData.find("y:") + 2;

        // Получаем размер
        size = stoi(shipData.substr(sPos, shipData.find(',', sPos) - sPos));
        // Получаем ориентацию
        orientation = shipData[oPos];
        // Получаем координаты
        x = stoi(shipData.substr(xPos, shipData.find(',', xPos) - xPos));
        y = stoi(shipData.substr(yPos));

        // Устанавливаем параметры корабля
        ship.setSize(size);
        ship.setOrientation(orientation == 'h'); // Преобразуем символ в булевое значение
        ship.setPosition(x, y); // Устанавливаем позицию

        enemyShips.push_back(ship); // Добавляем корабль в вектор
    }
}
