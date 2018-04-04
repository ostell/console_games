#pragma once
#ifndef SNK
#define SNK
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class Snake
{
private:
	struct coords {
		int x;
		int y;
	} food, block, temp, temp2;
	bool game_over, fed;
	std::vector<coords> snk_tail;
	int difficulty, width, height, dir, score;

public:
	Snake();
	void drawScene();
	void keyInput();
	void direction();
	int randNum(int range);
	int getScore();
	bool getGO();
	void NewApple();
	~Snake();
};

class WinFuncs {
public:
	WinFuncs();
	void ClearScreen();
	void ResizeConsole(int width, int height);
};

#endif
