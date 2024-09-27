#include "GameScreen.h"

GameScreen::GameScreen() {
    this->restart();
}

void GameScreen::render() {
    if (!this->gameEnd) {
        if (this->needRender) {
            system("cls");
            this->renderField(); // Отображение своего поля
            this->renderEnemyField(); // Отображение поля противника
            this->needRender = false;
        }
    }
}

void GameScreen::receiveData() {
    if (this->dataReceive) {
#ifdef _DEBUG
        cout << "dataReceive: " << this->dataReceive->x << " " << this->dataReceive->y << endl;
#endif
        this->enemySteps.push_back(*this->dataReceive);
        this->dataReceive = NULL;
        this->needRender = true;
    }

    this->shipUpdate();
}

void GameScreen::shipUpdate() {
    // Обновление статуса потопления кораблей
    for (auto& ship : ships) {
        if (ship.updateSunkStatus(this->enemySteps)) {
            // Если статус изменился на потопленный, добавляем выстрелы вокруг корабля
            for(auto& position : ship.getPositions()) {
                this->enemySteps.push_back(DataReceive(position.x - 1, position.y, true));
                this->enemySteps.push_back(DataReceive(position.x + 1, position.y, true));
                this->enemySteps.push_back(DataReceive(position.x, position.y - 1, true));
                this->enemySteps.push_back(DataReceive(position.x, position.y + 1, true));
                this->enemySteps.push_back(DataReceive(position.x - 1, position.y - 1, true));
                this->enemySteps.push_back(DataReceive(position.x - 1, position.y + 1, true));
                this->enemySteps.push_back(DataReceive(position.x + 1, position.y - 1, true));
                this->enemySteps.push_back(DataReceive(position.x + 1, position.y + 1, true));
            }
        }
    }
    for (auto& ship : enemyShips) {
        if (ship.updateSunkStatus(this->playerSteps)) {
            for(auto& position : ship.getPositions()) {
                this->playerSteps.push_back(DataReceive(position.x - 1, position.y, true));
                this->playerSteps.push_back(DataReceive(position.x + 1, position.y, true));
                this->playerSteps.push_back(DataReceive(position.x, position.y - 1, true));
                this->playerSteps.push_back(DataReceive(position.x, position.y + 1, true));
                this->playerSteps.push_back(DataReceive(position.x - 1, position.y - 1, true));
                this->playerSteps.push_back(DataReceive(position.x - 1, position.y + 1, true));
                this->playerSteps.push_back(DataReceive(position.x + 1, position.y - 1, true));
                this->playerSteps.push_back(DataReceive(position.x + 1, position.y + 1, true));
            }
        }
    }
}

void GameScreen::update() {
    static bool lock_click;

    lock_click = true;

    if(this->needWalk && this->gameEnd == false){
        int x, y;
        bool validShot = false;

        while (!validShot) {
            cout << "Your turn. " << endl << endl;
            cout << "Enter x: ";
            cin >> x;
            cout << "Enter y: ";
            cin >> y;

            // Проверка на корректность координат
            if (x < 0 || x >= gameSize || y < 0 || y >= gameSize) {
                cout << "Coordinates are out of bounds. Try again." << endl;
                continue;
            }

            // Проверка на выстрел в ту же клетку
            validShot = true;
            for (const auto& step : this->playerSteps) {
                if (step.x == x && step.y == y) {
                    validShot = false;
                    cout << "You have already shot at this cell. Try again." << endl;
                    break;
                }
            }
        }

        bool isHit = false;
        for (auto& ship : enemyShips) {
            if (ship.checkHit(x, y)) {
                isHit = true;
                break;
            }
        }

        this->playerSteps.push_back(DataReceive(x, y, true));

        this->needSend = true;
        this->dataSend = new DataReceive(x, y, isHit);
        this->needRender = true;
    }

    this->shipUpdate();
}

void GameScreen::renderField() {
    std::cout << "Your field:" << std::endl;
    for (int i = 0; i < gameSize; i++) {
        for (int j = 0; j < gameSize; j++) {
            bool isShipPresent = false;
            bool isHit = false;

            for (Ship ship : ships) {
                if (ship.checkHit(j, i)) {
                    isShipPresent = true;
                    break;
                }
            }

            for (const auto& step : enemySteps) {
                if (step.x == j && step.y == i) {
                    isHit = true;
                    break;
                }
            }

            if (isHit) {
                if (isShipPresent) {
                    std::cout << " X "; // Попадание по кораблю
                } else {
                    std::cout << " * "; // Попадание по пустой клетке
                }
            } else {
                if (isShipPresent) {
                    std::cout << " O "; // Корабль
                } else {
                    std::cout << " ~ "; // Пустая клетка
                }
            }
        }
        std::cout << std::endl; // Переход на новую строку
    }
}

void GameScreen::fill() {
    int choice;
    std::cout << "Choose filling method: 1 - Automatically, 2 - Manually: ";
    std::cin >> choice;
    if (choice == 1) {
        this->autoFill(); // Вызов функции автоматического заполнения
    }
    else {
        this->manualFill(); // Вызов функции ручного заполнения
    }
}

void GameScreen::autoFill() {
    int shipSizes[] = { 1, 1 };
    // int shipSizes[] = { 1, 1, 1, 1, 2, 2, 2, 3, 3, 4 };

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
                if (dx == 0 && dy == 0) {
                    continue; // Пропускаем текущую позицию
                };
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
    bool allPlayerShipsSunk = true;
    bool allEnemyShipsSunk = true;

    // Проверка всех кораблей игрока
    for (auto& ship : ships) {
        if (!ship.isSunkStatus()) {
            allPlayerShipsSunk = false;
            break;
        }
    }

    // Проверка всех кораблей противника
    for (auto& ship : enemyShips) {
        if (!ship.isSunkStatus()) {
            allEnemyShipsSunk = false;
            break;
        }
    }

    if ((allPlayerShipsSunk || allEnemyShipsSunk) && this->gameEnd == false) {
        system("cls");
        gameEnd = true;
        this->needRender = false;
        if (allEnemyShipsSunk) {
            cout << "You win. Congratulations!" << endl;
        } else {
            cout << "You lose. Try again!" << endl;
        }
    }
}

void GameScreen::restart() {
    this->_rinning = false;
    this->dataReceive = NULL;
    this->ships.clear(); // Очистка вектора кораблей при перезапуске
}

void GameScreen::renderEnemyField() {
    std::cout << std::endl << "Enemy field:" << std::endl;
    for (int i = 0; i < gameSize; i++) {
        for (int j = 0; j < gameSize; j++) {
            bool isShipPresent = false;
            bool isHit = false;
            bool isSunk = false;

            for (Ship& ship : enemyShips) {
                if (ship.checkHit(j, i)) {
                    isShipPresent = true;
                    if (ship.isSunkStatus()) {
                        isSunk = true;
                    }
                    break;
                }
            }

            for (const auto& step : playerSteps) {
                if (step.x == j && step.y == i) {
                    isHit = true;
                    break;
                }
            }

            if (isHit) {
                if (isShipPresent) {
                    std::cout << " X "; // Попадание по кораблю
                } else {
                    std::cout << " * "; // Попадание по пустой клетке
                }
            } else {
                std::cout << " ~ "; // Пустая клетка
            }
        }
        std::cout << std::endl; // Переход на новую строку
    }
}
