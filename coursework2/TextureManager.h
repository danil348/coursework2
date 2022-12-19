#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class TextureManager
{
public:
	static sf::Sprite* load(string pngPath, int width, int height);
	static sf::Sprite* load(string pngPath, int width, int height, sf::Color color);
private:

};

