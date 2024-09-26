#include "GameScreen.h"

GameScreen::GameScreen() {
    this->restart();
}

void GameScreen::render() {
    if (!this->gameEnd) {
        if (this->needRender) {
            this->renderField();
            this->needRender = false;
        }
    } else {
        if (this->zeroWins) {
            // Вывод экрана победы для игрока 1
        } else {
            // Вывод экрана победы для игрока 2
        }
    }
}

void GameScreen::update() {
    static bool lock_click;

    lock_click = true;

    if (this->dataReceive) {
        // Обработка полученных данных
        this->dataReceive = NULL;
    }
}

void GameScreen::renderField() {
    for (int i = 0; i < gameSize; i++) {
        for (int j = 0; j < gameSize; j++) {
            bool isShipPresent = false;

            for (Ship ship : ships) {
                if (ship.checkHit(j, i)) {
                    isShipPresent = true;
                    break;
                }
            }

            if (isShipPresent) {
                std::cout << " O "; // Корабль
            } else {
                std::cout << " ~ "; // Пустая клетка
            }
        }
        std::cout << std::endl; // Переход на новую строку
    }
}

void GameScreen::fill() {
    int choice;
    std::cout << "Выберите метод заполнения: 1 - Автоматически, 2 - Вручную: ";
    std::cin >> choice;
    if (choice == 1) {
        this->autoFill(); // Вызов функции автоматического заполнения
    } else {
        this->manualFill(); // Вызов функции ручного заполнения
    }
}

void GameScreen::autoFill() {
    int shipSizes[] = { 1, 1, 1, 1, 2, 2, 2, 3, 3, 4 }; 

    for (int size : shipSizes) {
        bool placed = false;
        while (!placed) {
            int x = rand() % this->gameSize;
            int y = rand() % this->gameSize;
            bool isHorizontal = rand() % 2;

            Ship newShip(size, isHorizontal);
            newShip.setPosition(x, y);

            if (canPlaceShip(newShip)) {
                this->ships.push_back(newShip);
                placed = true;
            }
        }
    }
}

bool GameScreen::canPlaceShip(const Ship& ship) {
    const auto& positions = ship.getPositions();

    for (const auto& position : positions) {
        int x = position.x;
        int y = position.y;

        // Проверка границ поля
        if (x < 0 || x >= gameSize || y < 0 || y >= gameSize) {
            return false; // Корабль выходит за границы поля
        }

        // Проверка на занятые клетки и расстояние
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue; // Пропускаем текущую позицию
                int checkX = x + dx;
                int checkY = y + dy;

                // Проверка, находится ли клетка в пределах поля
                if (checkX >= 0 && checkX < gameSize && checkY >= 0 && checkY < gameSize) {
                    // Проверка на занятость клетки
                    for (const auto& existingShip : ships) {
                        for (const auto& existingPosition : existingShip.getPositions()) {
                            if (existingPosition.x == checkX && existingPosition.y == checkY) {
                                return false; // Клетка занята
                            }
                        }
                    }
                }
            }
        }
    }
    return true; // Корабль можно разместить
}

void GameScreen::manualFill() {
    // Реализация ручного заполнения полей
}

void GameScreen::winsUpdate() {
    // Логика обновления состояния победы
}

void GameScreen::restart() {
    this->_rinning = false;
    this->dataReceive = NULL;
    this->ships.clear(); // Очистка вектора кораблей при перезапуске
}

