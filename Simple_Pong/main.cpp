#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <vector>
#include <time.h>
#include <math.h>
#include <thread>
#include "Pong.h"

int main(){

	Ball ball1;
	WinFuncs win;

	//Game loop
	while (true){
		ball1.t_pad.dir = STATIC;
		ball1.DrawScene();
		ball1.t_pad.getKeypress();
		ball1.checkCollision();
		ball1.moveBall();
		Sleep(20);
		win.ClearScreen();
		//std::this_thread::sleep_for(std::chrono::milliseconds(100 - (newgame.getScore() / 5)));
	}

	std::cin.get();
	return 0;
}