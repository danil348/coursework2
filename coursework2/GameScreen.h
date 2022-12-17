#pragma once

#include <SFML/Graphics.hpp>
#include "TextureManager.h"

using namespace std;

class GameScreen
{
public:
	GameScreen();
public:
	void render(sf::RenderWindow* window);
private:
	sf::Sprite* background;


	sf::Texture* back_texture;
	sf::Sprite* back_sprite;

};

