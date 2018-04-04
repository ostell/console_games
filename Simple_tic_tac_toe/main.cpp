/*
TIC-TAC-TOE
-----------
| o | x | o |
-----------
| o | x | o |
-----------
| x | o | o |
-----------
*/

#include <iostream>
#include <string>
#include <windows.h>
#include "TTToe.h"

int main(){
	int coordX = 0, coordY = 0;
	char temp;
	TToe toe;
	WinFuncs win;

	//Game setup
	std::cout << "WELCOME TO TIC-TAC-TOE!" << std::endl << std::endl;
	std::cout << "Player 1 will play with sumbol?" << std::endl;
	std::cin >> temp;
	toe.setSumbol(1, temp);
	std::cout << "Player 2 will play with sumbol?" << std::endl;
	std::cin >> temp;
	toe.setSumbol(2, temp);
	win.ClearScreen();

	toe.print_board();

	while (toe.getWinner()){
		toe.validate_input(coordX, coordY, "Player 1");
		toe.setBoard(coordX, coordY, 1);
		win.ClearScreen();
		toe.print_board();
		toe.win_check(coordX, coordY, 1);
		std::cout << std::endl;

		if (toe.getWinner()){
			toe.validate_input(coordX, coordY, "Player 2");
			toe.setBoard(coordX, coordY, 2);
			win.ClearScreen();
			toe.print_board();
			toe.win_check(coordX, coordY, 2);
			std::cout << std::endl;
		}
	}

	std::cin.get();
	return 0;
}


