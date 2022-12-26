#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class characters
{
public:
	characters() { this->picturePath = ""; };
	characters(string name, int width, int height, string imgPath);

public:
	void set_w_h(int width, int height);
	void setName(string name) { this->name = name; };
	void setPicturePath(string picturePath) { this->picturePath = picturePath; };
	void set_x(int x) { this->picture->setPosition(x, this->y); this->x = x; };
	void set_y(int y) { this->picture->setPosition(this->x, y); this->y = y; };
	void setSprite();
	void setSelected(bool selected) { this->selected = selected; };
public:
	int get_w() { return this->width; };
	int get_h() { return this->height; };
	int get_x() { return this->x; };
	int get_y() { return this->y; };	
	sf::Sprite* getSprite() { return this->picture; };
	bool getSelected() { return this->selected; };
	
	void checkLive();
public:
	string name;
	string picturePath;
	int attack;
	int armor;
	int health;
	int criticalDamage;
	int criticalDamage—hance;
	bool islive = true;

private:
	sf::Sprite* picture;
	int width, height;
	int x, y;

	bool selected = false;
};

