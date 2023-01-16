#pragma once
#include <iostream>
using namespace std;
struct Setting
{
	static bool sound;
	static bool fullscreen;
	static int screenWidth;
	static int screenHeight;
	static int resolution[4][2];

	static void next() 
	{
		for (int i = 0; i < 4; i++) {
			if (screenWidth == resolution[i][0]) {
				if (i == 3) {
					screenWidth = resolution[0][0];
					screenHeight = resolution[0][1];
				}
				else {
					screenWidth = resolution[i + 1][0];
					screenHeight = resolution[i + 1][1];
				}
				break;
			}
		}
	};

	static void prev()
	{
		for (int i = 0; i < 4; i++) {
			if (screenWidth == resolution[i][0]) {
					cout << "asdasd";
				if (i == 0) {
					screenWidth = resolution[3][0];
					screenHeight = resolution[3][1];
				}
				else {
					screenWidth = resolution[i - 1][0];
					screenHeight = resolution[i - 1][1];
				}
				break;
			}
		}
	};
};
