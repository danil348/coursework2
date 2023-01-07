#include "FontManager.h"

FontManager::FontManager()
{
	font.loadFromFile("fonts/ofont.ru_Cosmic Two.ttf");
}

sf::Text* FontManager::getText(wstring text, int pixelSize, sf::Color color, int x, int y)
{
	sf::Text* tmpText = new sf::Text;

	this->initText(tmpText, pixelSize, color, x, y);
	tmpText->setString(sf::String::fromUtf16(text.begin(), text.end()));

	return tmpText;
}

sf::Text* FontManager::getText(string text, int pixelSize, sf::Color color, int x, int y)
{
	sf::Text* tmpText = new sf::Text;

	this->initText(tmpText, pixelSize, color, x, y);
	tmpText->setString(sf::String::fromUtf16(text.begin(), text.end()));

	return tmpText;
}

sf::Text* FontManager::initText(sf::Text* text, int pixelSize, sf::Color color, int x, int y)
{
	text->setFont(font);
	text->setStyle(sf::Text::Bold);
	text->setCharacterSize(pixelSize);
	text->setFillColor(color);
	text->setPosition(x, y);

	return text;
}
