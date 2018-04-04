#include "TTToe.h"


TToe::TToe() {
	winner = true;

	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < ROWS; j++)
			board[i][j] = 0;
}

bool TToe::getWinner(void){
	return winner;
}

void TToe::setSumbol(int pl_num, char sinv){
	if (pl_num == 1)
		sumbol[0] = sinv;
	else
		sumbol[1] = sinv;
}

void TToe::setBoard(int X, int Y, int pl_num){
	board[X][Y] = pl_num;
}

//Main render function
void TToe::print_board(void){
	int i, j;

	std::cout << "TIC-TAC-TOE" <<std::endl;

	for (i = 0; i < ROWS; i++){
		std::cout << std::endl;
		std::cout << "-------" << std::endl;
		std::cout << "|";
		for (j = 0; j < ROWS; j++){
			switch (board[i][j]) {
			case 0: std::cout << " " << "|";
				break;
			case 1: std::cout << sumbol[0] << "|";
				break;
			case 2: std::cout << sumbol[1] << "|";
			}
		}
	}
	std::cout << std::endl;
	std::cout << "-------" << std::endl;
}

void TToe::print_board_raw(void){
	int i, j;

	std::cout << std::endl;

	for (i = 0; i < ROWS; i++){
		std::cout << std::endl;
		for (j = 0; j < ROWS; j++){
			std::cout << board[i][j] << " ";
		}
	}
	std::cout << std::endl;
	std::cout << "-------" << std::endl;
}

void TToe::validate_input(int &cX, int &cY, std::string pl){
	int X, Y;

	do {
		std::cout << pl << " enter row: " << std::endl;
		std::cin >> X;
		std::cout << pl << " enter column: " << std::endl;
		std::cin >> Y;
		if (board[X][Y] == 0 && X < ROWS && Y < ROWS){
			cX = X;
			cY = Y;
		}
		else
			std::cout << "Try again, outside of the table or overlaping values..." << std::endl;
	} while ((X >= 3) || (Y >= 3) || (board[X][Y] != 0));
}

void TToe::win_check(int cX, int cY, int player){

	//Up / down
	if (cX - 1 < ROWS && cY < ROWS && board[cX - 1][cY] == player && winner)
	if (cX - 2 < ROWS && board[cX + 2][cY] == player)
		win_game(player);
	else if (cX + 1 < ROWS && board[cX + 1][cY] == player)
		win_game(player);

	//Up- left / down - right
	if (cX - 1 < ROWS && cY + 1 < ROWS && board[cX - 1][cY + 1] == player && winner)
	if (cX - 2 < ROWS && cY + 2 < ROWS && board[cX - 2][cY + 2] == player)
		win_game(player);
	else if (cX + 1 < ROWS && cY - 1 < ROWS && board[cX + 1][cY - 1] == player)
		win_game(player);

	//Right / Left
	if (cX < ROWS && cY + 1 < ROWS && board[cX][cY + 1] == player && winner)
	if (cY + 2 < ROWS && board[cX][cY + 2] == player)
		win_game(player);
	else if (cY - 1 < ROWS && board[cX][cY - 1] == player)
		win_game(player);

	//Down - right / up - left     
	if (cX + 1 < ROWS && cY + 1 < ROWS && board[cX + 1][cY + 1] == player && winner)
	if (cX + 2 < ROWS && cY + 2 < ROWS && board[cX + 2][cY + 2] == player)
		win_game(player);
	else if (cX - 1 < ROWS && cY - 1 < ROWS && board[cX - 1][cY - 1] == player)
		win_game(player);

	//down / up    
	if (cX + 1 < ROWS && cY < ROWS && board[cX + 1][cY] == player && winner)
	if (cX + 2 < ROWS && board[cX + 2][cY] == player)
		win_game(player);
	else if (cX - 1 < ROWS && board[cX - 1][cY] == player)
		win_game(player);

	//down - left / up - right   
	if (cX + 1 < ROWS && cY - 1 < ROWS && board[cX + 1][cY - 1] == player && winner)
	if (cX + 2 < ROWS && cY - 2 < ROWS && board[cX + 2][cY - 2] == player)
		win_game(player);
	else if (cX - 1 < ROWS && cY + 1 < ROWS && board[cX - 1][cY + 1] == player)
		win_game(player);

	//left / right   
	if (cX < ROWS && cY - 1 < ROWS && board[cX][cY - 1] == player && winner)
	if (cY - 2 < ROWS && board[cX][cY - 2] == player)
		win_game(player);
	else if (cY + 1 < ROWS && board[cX][cY + 1] == player)
		win_game(player);

	//up - left / down - right  
	if (cX - 1 < ROWS && cY - 1 < ROWS && board[cX - 1][cY - 1] == player && winner)
	if (cX - 2 < ROWS && cY - 2 < ROWS && board[cX - 2][cY - 2] == player)
		win_game(player);
	else if (cX + 1 < ROWS && cY + 1 < ROWS && board[cX + 1][cY + 1] == player)
		win_game(player);
}

void TToe::win_game(int player){
	std::cout << "Player " << player << " wins!" << std::endl;
	winner = false;
}
