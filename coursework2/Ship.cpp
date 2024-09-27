#include "Ship.h"

Ship::Ship(int size, bool isHorizontal) : size(size), isSunk(false), isHorizontal(isHorizontal) {}

Ship::Ship(){
}

void Ship::setSize(int size){
    this->size = size;
}

void Ship::setOrientation(bool isHorizontal){
    this->isHorizontal = isHorizontal;
}

void Ship::setPosition(int x, int y) {
    for (int i = 0; i < size; ++i) {
        if (isHorizontal) {
            positions.push_back(Field(Field::FieldType::SHIP, x + i, y)); // Установка горизонтальной позиции
        } else {
            positions.push_back(Field(Field::FieldType::SHIP, x, y + i)); // Установка вертикальной позиции
        }
    }
}

bool Ship::checkHit(int x, int y) {
    for (const auto& position : positions) {
        if (position.x == x && position.y == y) {
            return true; // Попадание по кораблю
        }
    }
    return false; // Промах
}

bool Ship::isSunkStatus() {
    return isSunk; // Возвращает статус потопления
}

bool Ship::updateSunkStatus(std::vector<DataReceive> steps) {
    int hitCount = 0;
    for (const auto& position : positions) {
        for (const auto& step : steps) {
            if (position.x == step.x && position.y == step.y) {
                hitCount++;
                break;
            }
        }
    }
    if (hitCount == size) {
        isSunk = true;
        return true; // Статус изменился на потопленный
    }
    return false; // Статус не изменился
}