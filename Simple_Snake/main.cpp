#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Snake.h"

int main(){
	Snake newgame;
	WinFuncs win;
	bool end = true;

	win.ResizeConsole(450, 480);

	//Game loop
	while (!newgame.getGO()){
		//1. Clear screen buffer
		win.ClearScreen();
		//2. Get user input
		newgame.keyInput();
		//3. Change the direction of the snake, check if the snake is fed and check for game over
		newgame.direction();
		//4. Render the scene
		newgame.drawScene();

		//Make snake to move faster acording to how many apples she ate
		if (100 - (newgame.getScore() / 5) > 0)
			//Sleep(100 - (newgame.getScore() / 5));
			std::this_thread::sleep_for(std::chrono::milliseconds(100 - (newgame.getScore() / 5)));
	}

	std::cout << "The game has ended!" << std::endl << "Your score is: " << newgame.getScore() << std::endl;
	std::cin.get();
	return 0;
}
