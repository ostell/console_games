#include "Pong.h"

Table::Table(){
	score_p1 = 0;
	score_p2 = 0;
}

void Table::incScore_p1(){
	score_p1++;
}

void Table::incScore_p2(){
	score_p2++;
}

unsigned int Table::getScore_p1(){
	return score_p1;
}

unsigned int Table::getScore_p2(){
	return score_p2;
}

void Table::displayScore(){
	std::cout << "Score: " << getScore_p1() << " - " << getScore_p2() << std::endl;
}


