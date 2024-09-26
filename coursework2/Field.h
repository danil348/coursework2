#pragma once

class Field
{
public:
	Field() {};

	static enum FieldType {
		EMPTY,
		SHIP,
		HIT,
		MISS,
		DESTROYED
	};

	Field(FieldType fieldType, int x, int y) {
		this->fieldType = fieldType;
		this->x = x;
		this->y = y;
	}
	FieldType fieldType = FieldType::EMPTY;
	int x = 0;
	int y = 0;
};