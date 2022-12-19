#include "FontManager.h"

FontManager::FontManager()
{
	font.loadFromFile("fonts/ofont.ru_Cosmic Two.ttf");
}

sf::Text* FontManager::getText(wstring text, int pixelSize, sf::Color color, int x, int y)
{
	sf::Text* tmpText = new sf::Text;

	tmpText->setFont(font);
	tmpText->setStyle(sf::Text::Bold);

	tmpText->setString(sf::String::fromUtf16(text.begin(), text.end()));
	tmpText->setCharacterSize(pixelSize);
	tmpText->setFillColor(color);
	tmpText->setPosition(x, y);
	return tmpText;
}

sf::Text* FontManager::getText(string text, int pixelSize, sf::Color color, int x, int y)
{
	sf::Text* tmpText = new sf::Text;

	tmpText->setFont(font);
	tmpText->setStyle(sf::Text::Bold);

	tmpText->setString(sf::String::fromUtf16(text.begin(), text.end()));
	tmpText->setCharacterSize(pixelSize);
	tmpText->setFillColor(color);
	tmpText->setPosition(x, y);
	return tmpText;
}
