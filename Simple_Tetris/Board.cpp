#include "Tetris.h"

//Init of the board
Board::Board(){

	GameOver = true;
	Peace = true;
	score = 0;

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++){
			if (j == 0 || i == HEIGHT - 1 || j == WIDTH - 1){
				BoardArr[i][j] = 1;
			}
			else
				BoardArr[i][j] = 0;
		}
	}
}

//Print the element in the next section
void Board::DisplayNextPart(coords nextpeace[PARTSELEM]){
	bool flag;

	for (int i = 0; i < PARTSELEM + 1; i++){
		for (int j = 0; j < PARTSELEM + 1; j++){
			flag = true;
			if (j == 0){
				if (i == 2){
					std::cout << "Next  #";
				}
				else {
					std::cout << "      #";
				}
			}
			if (i == PARTSELEM || j == PARTSELEM){
				std::cout << "#";
				flag = false;
			}

			for (int k = 0; k < PARTSELEM; k++){
				if (nextpeace[k].x == j && nextpeace[k].y == i){
					std::cout << "#";
					flag = false;
					break;
				}
			}
			if (flag)
				std::cout << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//MAIN RENDER FUNCTION...Print the borders of the board, all blocks, next element and the score
void Board::DisplayBoard(){
	//Display the borders of the board and all the blocks
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++){
			if (BoardArr[i][j] == 1)
				std::cout << "#";
			else
				std::cout << " ";
		}
		std::cout << std::endl;
	}
	//Display the next element
	DisplayNextPart(NextPartDisplay);
	//Display the score
	std::cout << "Score: " << getScore();
}

//Display (hardcode) "store" peace on the board
void Board::StoreElement(coords temp[PARTSELEM]){
	for (int i = 0; i <= PARTSELEM; i++)
		BoardArr[temp[i].y][temp[i].x] = 1;
}

//Scan the whole board for full rows and return the full row number 
void Board::FullRow(){
	int count;
	int scoreCnt = 0;

	for (int i = HEIGHT - 2; i > 1; --i)
	{
		count = 0;
		for (int j = 1; j < WIDTH - 1; ++j){
			if (BoardArr[i][j] == 1)
				count++;
		}
		if (count == FULLROW){
			DeleteRow(i);
			i++;
			++scoreCnt;
		}
	}

	//increase the score acording to rows cleared
	switch (scoreCnt){
	case 1: score = score + 40;
		break;
	case 2: score = score + 100;
		break;
	case 3: score = score + 300;
		break;
	case 4: score = score + 1200;
		break;
	default:
		break;
	}
}

//If there is full row, delete it and move the upper peaces down
void Board::DeleteRow(char RowNum){
	if (RowNum != NOROWSTODEL){
		for (int j = 1; j < WIDTH - 1; ++j)
			BoardArr[RowNum][j] = 0;

		for (int i = RowNum; i >= 1; --i)
		for (int k = 1; k < WIDTH - 1; ++k)
			BoardArr[i][k] = BoardArr[i - 1][k];
	}
}

void Board::IsGameOver(){

	for (int j = 1; j < WIDTH - 1; j++){
		if (BoardArr[0][j] == 1){
			GameOver = false;
			break;
		}
		else
			GameOver = true;
	}
}

bool Board::getGameOver(){
	return GameOver;
}

bool Board::getNextPeace(){
	return Peace;
}

bool Board::setNextPeace(bool val){
	return Peace = val;
}

int Board::getScore(){
	return score;
}
