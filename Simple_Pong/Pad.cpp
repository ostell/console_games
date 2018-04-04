#include "Pong.h"

Pad::Pad() {
	coords_i temp;
	for (int i = 0; i < PADSIZE; ++i){
		temp.x = HEIGHT / 2 - 3 + i;
		temp.y = 0;
		pad_vec_p1.push_back(temp);
	}

	for (int i = 0; i < PADSIZE; ++i){
		temp.x = HEIGHT / 2 - 3 + i;
		temp.y = WIDTH - 1;
		pad_vec_p2.push_back(temp);
	}
	//move = 0;
	dir = STATIC;
}

bool Pad::checkCollision(int numpad, int dir) {
	int tempYarr[PADSIZE];

	if (numpad == 1){
		for (int i = 0; i < PADSIZE; ++i)
			tempYarr[i] = pad_vec_p1[i].x + dir;

		for (int i = 0; i < PADSIZE; ++i){
			if (tempYarr[i] <= 0 || tempYarr[i] >= HEIGHT - 1)
				return 1;
		}
		return 0;
	}

	if (numpad == 2){
		for (int i = 0; i < PADSIZE; ++i)
			tempYarr[i] = pad_vec_p2[i].x + dir;

		for (int i = 0; i < PADSIZE; ++i){
			if (tempYarr[i] <= 0 || tempYarr[i] >= HEIGHT - 1)
				return 1;
		}
		return 0;
	}
}

void Pad::movePad(int numpad, int dir){

	if (numpad == 1){
		for (int i = 0; i < PADSIZE; ++i)
			pad_vec_p1[i].x = pad_vec_p1[i].x + dir;
		return;
	}

	if (numpad == 2){
		for (int i = 0; i < PADSIZE; ++i)
			pad_vec_p2[i].x = pad_vec_p2[i].x + dir;
		return;
	}
}

void Pad::getKeypress(){
		if (_kbhit()){
			switch (_getch()){
				//up pad 1
			case 'w':
				if (!checkCollision(1, -1))
					movePad(1, -1);
					dir = UP;
				break;
				//down pad 1
			case 's':
				if (!checkCollision(1, 1))
					movePad(1, 1);
					dir = DOWN;
				break;
			case 'o':
				if (!checkCollision(2, -1))
					movePad(2, -1);
					dir = UP;
				break;
				//down pad 2
			case 'l':
				if (!checkCollision(2, 1))
					movePad(2, 1);
					dir = DOWN;
				break;
			}
		}
}

std::vector<coords_i> Pad::getPad_p1(){
	return pad_vec_p1;
}

std::vector<coords_i> Pad::getPad_p2(){
	return pad_vec_p2;
}
