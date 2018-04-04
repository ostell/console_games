#include <iostream>
#include <chrono>
#include <thread>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "Tetris.h"

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

//Declaration of the board array
char BoardArr[HEIGHT][WIDTH];

//Array with all the different block shapes
coords iniPart[PARTSNUM][PARTSELEM] = {
	//L
	{ { 0, 0 }, { -1, 1 }, { -1, 0 }, { 1, 0 } },
	//Mirrored L
	{ { 0, 0 }, { -1, -1 }, { -1, 0 }, { 1, 0 } },
	//Z
	{ { 0, 0 }, { -1, 0 }, { 0, 1 }, { 1, 1 } },
	//Mirrored Z
	{ { 0, 0 }, { -1, 1 }, { 0, 1 }, { 1, 0 } },
	//T
	{ { 0, 0 }, { -1, 0 }, { 0, -1 }, { 0, 1 } },
	//I
	{ { 0, 0 }, { 0, -1 }, { 0, 1 }, { 0, 2 } },
	//Cube
	{ { 0, 0 }, { -1, 0 }, { -1, -1 }, { 0, -1 } },
};

//Initialization translation point
coords iniPoint = { 2, 5 };
//Initialization rotation point
coords iniRotate = { -3, 7 };
//Declaration of the current part
coords TempPart[PARTSELEM];
//Declaration of the Indexes for displaying the next part
coords NextPartDisplay[PARTSELEM];
//Declaration of the next part
coords NextPart[PARTSELEM];


int main(){

	srand((unsigned int)time(NULL));;

	Board boardNew;
	Peace peaceNew;
	WinFuncs win;

	win.ResizeConsole(300, 450);
	//Game loop
	while (boardNew.getGameOver()){
		//Check for full rows to delete and score
		boardNew.FullRow();
		//Enable peace loop
		boardNew.setNextPeace(true);
		iniPoint.y = 1;
		iniPoint.x = 5;
		//Create next peace
		peaceNew.CreateNextPeace();
		//Display the current peace on the board array
		peaceNew.DisplayPeace(TempPart);

		//Enter the peace loop
		while (boardNew.getNextPeace()){
			static int counter = 0;
			//Checks user unput
			peaceNew.KeyInput();
			//Render the board
			boardNew.DisplayBoard();
			//Abjust the game speed
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			//Every 3-rd iteration move the peace one position down
			if (counter == 3){
				//Delete the peace in the current position
				peaceNew.DeletePeace(TempPart);
				//Check for collisions with the walls of other blocks
				if (!peaceNew.CollisionDetection(TempPart, 1, 0)){
					iniPoint.y++;
					//Assign peace to new coordinates
					peaceNew.PeaceAssign(1, 0);
					//Copy the peace to the board
					peaceNew.DisplayPeace(TempPart);
					//newBoard.setNextPeace(true);
				}
				else {
					//If collision is detected exit the peace loop
					boardNew.setNextPeace(false);
					//Copy the peace to the board
					peaceNew.DisplayPeace(TempPart);
					//newBoard.IsGameOver();
				}
				counter = 0;
			}
			counter++;
			//Clear the screen to get new frame
			//boardNew.ClearBoard();
			win.ClearScreen();
		}
		//Copy next part to the current part
		peaceNew.CopyNextToCurrentPeace();
		//Check if there are elements in the first row
		boardNew.IsGameOver();
	}

	std::cout << "GAME OVER!" << std::endl;
	std::cout << "Your score is: " << boardNew.getScore();
	std::cin.get();
	return 0;
}
