#ifndef PONG_H
#define PONG_H

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <vector>
#include <time.h>
#include <math.h>
#include <thread>

#define WIDTH 42
#define HEIGHT 22
#define PADSIZE 5
#define PI 3.14159265
#define FIRST_PAD 1
#define SECOND_PAD 2
#define STATIC 0
#define UP -1
#define DOWN 1

struct coords {
	float x;
	float y;
};

struct coords_i {
	int x;
	int y;
};

//class for the table things and score
class Table {
private:
	unsigned int score_p1, score_p2;
public:
	Table();
	unsigned int getScore_p1(); //getter p1 //RDY
	unsigned int getScore_p2(); //getter p2 //RDY
	void incScore_p1(); //increase the score of p1 by one //RDY
	void incScore_p2(); //increase the score of p2 by one //RDY
	void displayScore();
};

//class for the pad properties, movement, check collisions with the walls
class Pad {
private:
	std::vector<coords_i> pad_vec_p1, pad_vec_p2;
public:
	int dir;
	int move;
	Pad(); //Init draw the two pads //RDY
	void getKeypress(); // Detect keypresses for (1) pad of (2) pad  //RDY
	void movePad(int, int); //move first of second pad up or down //RDY 
	bool checkCollision(int, int); // Check if pad collides with top or the bottom of the board //RDY
	std::vector<coords_i> getPad_p1(); // getter to help the ballCollision function //RDY
	std::vector<coords_i> getPad_p2(); // getter to help the ballCollision function //RDY
};

//class for the ball properties
class Ball {
private:
	coords ballc, offset;
	Table t_table;
	float angle;
public:
	Pad t_pad;
	Ball(); //initialize the ball's parameters //RDY
	void moveBall(); //move the ball to the next position //RDY
	//float rndNum(bool);
	int rndAngle(); //generate random angle for the beggining of the game //RDY
	void initOffset(int); //generate random offset for the begginging //RDY
	coords getBallCoords(); //getter //RDY //i want to kiss you now! ;)
	void setOffset(float x, float y); //setter //RDY
	void checkCollision(); //check if the ball collides with the top, bottom, left pad, right pad, left side or right side
	void DrawScene();
	int round(float);
	void calcOffset(float Angle, int pad);
	float getAngle();
};

class WinFuncs {
public:
	WinFuncs();
	void ClearScreen();
	void ResizeConsole(int width, int height);
};

#endif