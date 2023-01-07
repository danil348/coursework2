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

void characters::checkLive() 
{
	if (this->health <= 0) {
		this->health = 0;
		this->islive = false;
	}
}

int& characters::getCharacteristic(int characteristicNumber)
{
	switch (characteristicNumber) {
	case this->_attack: return this->attack;
	case this->_armor: return this->armor;
	case this->_health: return this->health;
	case this->_criticalDamage: return this->criticalDamage;
	case this->_criticalDamage—hance: return this->criticalDamage—hance;
	default: return *new int;
	}
}

string characters::getCharacteristicName(int characteristicNumber)
{
	switch (characteristicNumber) {
	case this->_attack: return "Attack";
	case this->_armor: return "Armor";
	case this->_health: return "Health";
	case this->_criticalDamage: return "CriticalDamage";
	case this->_criticalDamage—hance: return "CriticalDamageChance";
	default: return *new string;
	}
}

