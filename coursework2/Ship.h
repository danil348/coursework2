#pragma once
#include "Field.h"
#include <vector>

class Ship {
private:
    std::vector<Field> positions; // Вектор для хранения позиций корабля
    int size; // Размер корабля
    bool isSunk; // Флаг, указывающий, потоплен ли корабль
    bool isHorizontal; // Флаг, указывающий, расположен ли корабль горизонтально

public:
    Ship();
    Ship(int size, bool isHorizontal); // Конструктор для инициализации размера и положения корабля
    
    void setPosition(int x, int y); // Установка позиции корабля
    void setSize(int size);
    void setOrientation(bool isHorizontal);

    bool getOrientation() const { return this->isHorizontal; }
    
    bool checkHit(int x, int y); // Проверка попадания по кораблю
    bool isSunkStatus(); // Проверка, потоплен ли корабль
    
    std::vector<Field> getPositions() const { return this->positions; } // Метод для получения позиций корабля
};