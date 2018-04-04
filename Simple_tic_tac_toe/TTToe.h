#ifndef TICT
#define TICT

#include <iostream>
#include <string>
#include <windows.h>
#define ROWS 3
#define PLY 2

class TToe {
private:
	char sumbol[PLY];
	bool winner;
	int board[ROWS][ROWS];
public:
	TToe();
	void setSumbol(int pl_num, char sinv);
	void setBoard(int X, int Y, int pl_num);
	bool getWinner(void);
	void print_board(void);
	void print_board_raw(void);
	void validate_input(int &cX, int &cY, std::string pl);
	void win_check(int cX, int cY, int player);
	void win_game(int player);
};

class WinFuncs {
public:
	WinFuncs();
	void ClearScreen();
	void ResizeConsole(int width, int height);
};

#endif