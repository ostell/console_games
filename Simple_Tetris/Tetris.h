#ifndef TETRIS_H
#define TETRIS_H

#include <iostream>
#include <chrono>
#include <thread>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define PARTSNUM 7
#define PARTSELEM 4
#define WIDTH 12
#define HEIGHT 21
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define FULLROW 10
#define NOROWSTODEL 69
#define Y_NEXT_INIT 2
#define X_NEXT_INIT 1

extern struct coords {
	char y;
	char x;
};

extern char BoardArr[HEIGHT][WIDTH];
extern coords iniPart[PARTSNUM][PARTSELEM];
extern coords iniPoint;
extern coords iniRotate;
extern coords TempPart[PARTSELEM];
extern coords NextPartDisplay[PARTSELEM];
extern coords NextPart[PARTSELEM];

class WinFuncs {
public:
	WinFuncs();
	void ClearScreen(); // RDY
	void ResizeConsole(int width, int height);
};
//The Board class
class Board {
private:
	bool GameOver;
	bool Peace;
	int score;
public:
	Board(); // RDY
	void DisplayBoard(); // RDY
	void DisplayNextPart(coords nextpeace[PARTSELEM]); //RDY
	void StoreElement(coords temp[PARTSELEM]); // RDY
	void FullRow(); // RDY
	void DeleteRow(char RowNum); // RDY
	void IsGameOver(); // RDY
	bool getNextPeace(); // RDY
	bool setNextPeace(bool val); //RDY
	int getScore(); //RDY
	bool Board::getGameOver(); //RDY
};

//Peaces class
class Peace {
public:
	Board newBoard;
	Peace();
	void RotatePeace(); //RDY
	bool CollisionDetection(coords peace[PARTSELEM], char iniY, char iniX); //RDY
	void DisplayPeace(coords peace[PARTSELEM]); //RDY
	void DeletePeace(coords peace[PARTSELEM]); //RDY
	void KeyInput(); //RDY
	char MinElem(coords peace[PARTSELEM]); //RDY
	char MaxElem(coords peace[PARTSELEM]); //RDY
	void PeaceAssign(char offsetY, char offsetX); //RDY
	void CreateNextPeace();
	void CopyNextToCurrentPeace();
	//void IndexToArrTransform(coords parts[PARTSELEM], int offset_y, int offset_x);
};

#endif
