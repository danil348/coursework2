#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class FontManager
{
public:
	FontManager();
	sf::Text* getText(wstring text, int pixelSize, sf::Color color, int x, int y);
	sf::Text* getText(string text, int pixelSize, sf::Color color, int x, int y);
private:
	sf::Text* initText(sf::Text* text, int pixelSize, sf::Color color, int x, int y);
	sf::Font font;
};
