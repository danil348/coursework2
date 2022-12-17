#include "TextureManager.h"

sf::Sprite* TextureManager::load(string pngPath, int width, int height)
{
    sf::Texture* tmpTexture = new sf::Texture;
    sf::Sprite* tmpSprite = new sf::Sprite;
    
    tmpTexture->loadFromFile(pngPath);
    //tmpImage.createMaskFromColor(sf::Color(128, 128, 192));
    tmpSprite->setTexture(*tmpTexture);

    tmpSprite->setScale(
        float(width) / float(tmpSprite->getTexture()->getSize().x),
        float(height) / float(tmpSprite->getTexture()->getSize().y)
    );

    return tmpSprite;
}
