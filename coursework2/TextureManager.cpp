#include "TextureManager.h"

sf::Sprite* TextureManager::load(string pngPath, int width, int height)
{
    sf::Texture* tmpTexture = new sf::Texture;
    sf::Sprite* tmpSprite = new sf::Sprite;
 
    tmpTexture->loadFromFile(pngPath);
    tmpSprite->setTexture(*tmpTexture);

    tmpSprite->setScale(
        float(width) / float(tmpSprite->getTexture()->getSize().x),
        float(height) / float(tmpSprite->getTexture()->getSize().y)
    );

    return tmpSprite;
}

sf::Sprite* TextureManager::load(string pngPath, int width, int height, sf::Color color)
{
    sf::Texture* tmpTexture = new sf::Texture;
    sf::Image* tmpImage = new sf::Image;
    sf::Sprite* tmpSprite = new sf::Sprite;

    tmpImage->loadFromFile(pngPath);
    tmpImage->createMaskFromColor(color);
    tmpTexture->loadFromImage(*tmpImage);
    tmpSprite->setTexture(*tmpTexture);

    tmpSprite->setScale(
        float(width) / float(tmpSprite->getTexture()->getSize().x),
        float(height) / float(tmpSprite->getTexture()->getSize().y)
    );

    return tmpSprite;
}
