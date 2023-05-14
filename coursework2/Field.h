#pragma once

class Field
{
public:
	Field() {};
	Field(bool isZero, bool isOccupied) {
		this->isZero = isZero;
		this->isOccupied = isOccupied;
	}
	bool isZero;
	bool isOccupied;
	int x = 0;
	int y = 0;
};