#include "Snake.h"

Snake::Snake()
{
	width = 30;
	height = 30;
	game_over = false;
	difficulty = 1;
	srand((int)time(0));
	dir = 0;
	score = 0;
	//dir = LEFT;
	fed = false;
	temp.x = width/2;
	temp.y = height/2;
	for (int i = 0; i < 5; ++i){
		temp.y = height / 2 - i;
		snk_tail.push_back(temp);
	}
	temp.x = 0;
	temp.y = 0;
	NewApple();
	//food.x = randNum(30);
	//food.y = randNum(30);
}

Snake::~Snake()
{
	std::cout << "bye bye..." << std::endl;
}

bool Snake::getGO(){
	return game_over;
}

int Snake::randNum(int range){
	int r = (rand() % range);
	while (r == 0){
		r = (rand() % range);
	}

	return r;
}

void Snake::NewApple(){
	bool flag = true;
	int r_y;
	int r_x;

	while (flag){
		r_y = randNum(30);
		r_x = randNum(30);

		for (int cnt = 0; cnt < snk_tail.size(); cnt++){
			if (r_x == snk_tail[cnt].x && r_y == snk_tail[cnt].y){
				flag = true;
				break;
			}
			else
				flag = false;
		}
	}
	food.y = r_y;
	food.x = r_x;
}


int Snake::getScore(){
	return score;
}

//Main render function
void Snake::drawScene() {
	int i, j;
	bool space;
	fed = false;

	for (i = 0; i <= height; i++){
		for (j = 0; j <= width; j++){
			space = true;
			if (i == 0 || i == width || j == 0 || j == height){
				std::cout << "H";
			}
			else if (i == food.x && j == food.y) {
				std::cout << "@";
			}
			else {
				for (std::vector<coords>::iterator k = snk_tail.begin(); k != snk_tail.end(); ++k){
					if (i == k->x && j == k->y){
						std::cout << "o";
						space = false;
					}
				}
			if (space)
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}

	if (snk_tail[0].x == food.x && snk_tail[0].y == food.y){
		NewApple();
		//food.x = randNum(30);
		//food.y = randNum(30);
		fed = true;
		score = score + 10;
	}
	if (snk_tail[0].x == height || snk_tail[0].x == 0 || snk_tail[0].y == width || snk_tail[0].y == 0){
		game_over = true;
	}


}

//Game logic: Move the snake, Is the snake fed, Is the game over
void Snake::direction(){
	unsigned int cnt;

	switch (dir){
	case UP:
		//x--
		temp.x = snk_tail[0].x;
		temp.y = snk_tail[0].y;
		temp.x--;
		snk_tail.insert(snk_tail.begin(), temp);
		if (!fed)
			snk_tail.pop_back();
		break;
	case DOWN:
		//x++
		temp.x = snk_tail[0].x;
		temp.y = snk_tail[0].y;
		temp.x++;
		snk_tail.insert(snk_tail.begin(), temp);
		if (!fed)
			snk_tail.pop_back();
		break;
	case LEFT:
		//y--
		temp.x = snk_tail[0].x;
		temp.y = snk_tail[0].y;
		temp.y--;
		snk_tail.insert(snk_tail.begin(), temp);
		if (!fed)
			snk_tail.pop_back();
		break;
	case RIGHT:
		//y++
		temp.x = snk_tail[0].x;
		temp.y = snk_tail[0].y;
		temp.y++;
		snk_tail.insert(snk_tail.begin(), temp);
		if (!fed)
			snk_tail.pop_back();
		break;
	}

	for (cnt = 1; cnt < snk_tail.size(); cnt++)
	if (snk_tail[0].x == snk_tail[cnt].x && snk_tail[0].y == snk_tail[cnt].y)
		game_over = true;
}

void Snake::keyInput() {
	if (_kbhit()){
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		}
	}
}

