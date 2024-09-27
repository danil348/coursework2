#pragma once
class DataReceive
{
public:
	DataReceive(): x(0), y(0), isPlayerStep(false) {};
	~DataReceive() {};

	DataReceive(int x, int y, bool isPlayerStep): 
		x(x), y(y), isPlayerStep(isPlayerStep) {}

public:
	int x;
	int y;
	bool isPlayerStep;
};

