#include "characters.h"

characters::characters(string name, int width, int height, string imgPath)
{
	this->name = name;
	this->width = width;
	this->height = height;
	this->picture = TextureManager::load(imgPath, width, height);
	this->picturePath = imgPath;
}

void characters::set_w_h(int width, int height)
{
	this->width = width;
	this->height = height;
	if (this->picture) {
		this->picture->setScale(
			float(width) / float(this->picture->getTexture()->getSize().x),
			float(height) / float(this->picture->getTexture()->getSize().y)
		);
	}
}

void characters::setSprite()
{
	if (this->picturePath != "") {
		this->picture = TextureManager::load(picturePath, 10, 10);
	}
}
