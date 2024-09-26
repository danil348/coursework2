#include "Game.h"

using namespace sf;
int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RU");

	Game game;

	game.gameRun();
}