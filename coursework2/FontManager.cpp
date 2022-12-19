#include "FontManager.h"

FontManager::FontManager()
{
	font.loadFromFile("fonts/SpecialElite-Regular.ttf");
}

sf::Text* FontManager::getText(string text, int pixelSize, sf::Color color, int x, int y)
{
	sf::Text* tmpText = new sf::Text;
	tmpText->setFont(font);
	tmpText->setStyle(sf::Text::Bold);

	tmpText->setString(text);
	tmpText->setCharacterSize(pixelSize);
	tmpText->setFillColor(color);
	tmpText->setPosition(x, y);
	return tmpText;
}
