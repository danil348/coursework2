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
	void set_x(int x) { this->x = x; };
	void set_y(int y) { this->y = y; };
	void setSprite();
public:
	int get_w() { return this->width; };
	int get_h() { return this->height; };
	int get_x() { return this->x; };
	int get_y() { return this->y; };	
	string getName() { return this->name; };
	string getPicturePath() { return this->picturePath; };
	sf::Sprite* getSprite() { return this->picture; };
private:
	string name;
	string picturePath;
	sf::Sprite* picture;
	int width, height;
	int x, y;
};

