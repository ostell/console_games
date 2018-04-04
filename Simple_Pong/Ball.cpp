#include "Pong.h"

Ball::Ball(){
	srand((unsigned)time(NULL));
	ballc.x = WIDTH / 2;
	ballc.y = HEIGHT / 2;
	initOffset(rndAngle());
	//ClearScreen();
}

void Ball::initOffset(int Angle){
	offset.x = (float)sin(Angle*(PI/180));
	offset.y = (float)cos(Angle*(PI/180));
	offset.y = -1 * offset.y;
	angle = Angle;
}

void Ball::moveBall() {
	ballc.x = ballc.x + offset.x;
	ballc.y = ballc.y + offset.y;
}

void Ball::calcOffset(float angle, int pad){
	if (pad == FIRST_PAD){
		if (angle > 0 && angle < 180){
			initOffset(round(angle));
			return;
		}
	}

	if (pad == SECOND_PAD){
		if (angle < 360 && angle > 180){
			initOffset(round(angle));
			return;
		}
	}
}

void Ball::checkCollision() {
	std::vector<coords_i> t_pad1 = t_pad.getPad_p1();
	std::vector<coords_i> t_pad2 = t_pad.getPad_p2();
	float angle;

	//check for collisions with left or right side
	if (round(ballc.x + offset.x) >= WIDTH || round(ballc.x + offset.x) <= -1){
		if (round(ballc.x + offset.x) >= WIDTH)
			t_table.incScore_p1();
		if (round(ballc.x + offset.x) <= 0)
			t_table.incScore_p2();

		offset.x = -1 * offset.x;
		angle = (atan2(offset.x, -offset.y) * (180 / PI));
		angle = (angle < 0) ? angle + 360 : angle;
		Ball::angle = angle;
		return;
	}

	//check collisions with the top or the bottom
	else if (round(ballc.y + offset.y) >= HEIGHT-1 || round(ballc.y + offset.y) <= 0){
		offset.y = -1 * offset.y;
		angle = (atan2(offset.x, -offset.y) * (180 / PI));
		angle = (angle < 0) ? angle + 360 : angle;
		Ball::angle = angle;
		return;
	}

	//check collisions with the first pad
	for (int i = 0; i < PADSIZE; i++)
		if (round(ballc.y + offset.y) == t_pad1[i].x && round(ballc.x + offset.x) == t_pad1[i].y){
			offset.x = -1 * offset.x;
			angle = (atan2(offset.x, -offset.y) * (180 / PI));
			angle = (angle < 0) ? angle + 360 : angle;
			Ball::angle = angle;

			//ball coming from TOP and pad is movind DOWN
			if (t_pad.dir == DOWN && offset.y > 0){
				angle = angle + 15;
				calcOffset(angle, FIRST_PAD);
			}
			//ball coming from TOP and pad is movind UP
			else if (t_pad.dir == UP && offset.y > 0){
				angle = angle - 15;
				calcOffset(angle, FIRST_PAD);
			}
			//ball coming from bottom and pad is movind DOWN
			else if (t_pad.dir == UP && offset.y < 0){
				angle = angle - 15;
				calcOffset(angle, FIRST_PAD);
			}
			//ball coming from bottom and pad is movind DOWN
			else if (t_pad.dir == DOWN && offset.y < 0){
				angle = angle + 15;
				calcOffset(angle, FIRST_PAD);
			}

			return;
		}

	//check collisions with the second pad
	for (int i = 0; i < PADSIZE; i++)
			if (round(ballc.y + offset.y) == t_pad2[i].x && round(ballc.x + offset.x) == t_pad2[i].y){

				offset.x = -1 * offset.x;
				angle = (atan2(offset.x, -offset.y) * (180 / PI));
				angle = (angle < 0) ? angle + 360 : angle;
				Ball::angle = angle;
				//ball coming from TOP and pad is movind DOWN
				if (t_pad.dir == DOWN && offset.y > 0){
					angle = angle - 15;
					calcOffset(angle, SECOND_PAD);
				}
				//ball coming from TOP and pad is movind UP
				else if (t_pad.dir == UP && offset.y > 0){
					angle = angle + 15;
					calcOffset(angle, SECOND_PAD);
				}
				//ball coming from bottom and pad is movind UP
				else if (t_pad.dir == UP && offset.y < 0){
					angle = angle + 15;
					calcOffset(angle, SECOND_PAD);
				}
				//ball coming from bottom and pad is movind DOWN
				else if (t_pad.dir == DOWN && offset.y < 0){
					angle = angle - 15;
					calcOffset(angle, SECOND_PAD);
				}
			}
}

//Main render function
void Ball::DrawScene(){
	std::vector<coords_i> t1_pad = t_pad.getPad_p1();
	std::vector<coords_i> t2_pad = t_pad.getPad_p2();
	bool space;

	for (int i = 0; i < HEIGHT; ++i){
		for (int j = 0; j < WIDTH; ++j){
			space = true;
			if (i == 0 || i == HEIGHT - 1)
				std::cout << "=";
			else if (i == round(ballc.y) && j == round(ballc.x)) {
				std::cout << "@";
			}
			else {
				for (std::vector<coords_i>::iterator k = t1_pad.begin(); k != t1_pad.end(); ++k)
				if (i == k->x && j == k->y){
					std::cout << "H";
					space = false;
				}
				for (std::vector<coords_i>::iterator m = t2_pad.begin(); m != t2_pad.end(); ++m)
				if (i == m->x && j == m->y){
					std::cout << "H";
					space = false;
				}
				if (space)
					std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
	t_table.displayScore();
	std::cout << std::endl;
	std::cout << "Angel of the ball: " << getAngle();
}

coords Ball::getBallCoords(){
	return ballc;
}

void Ball::setOffset(float x, float y){
	offset.x = x;
	offset.y = y;
}

int Ball::rndAngle(){
	int numb = rand() % 360;

	while (numb == 0 || numb == 180 || numb == 360)
		numb = rand() % 360;
	angle = numb;
	return numb;
}

int Ball::round(float num){
	return (num >= 0) ? (int)(num + 0.5) : (int)(num - 0.5);
}

float Ball::getAngle(){
	return angle;
}

/*
float Ball::rndNum(bool nonzero = 0){
float scale=RAND_MAX+1.;
float base=rand()/scale;
float fine=rand()/scale;
int sign = rand()%2;
float number =  (sign == 1) ? base+fine/scale : -1*(base+fine/scale);

if(nonzero){
while(number == 0){
base=rand()/scale;
fine=rand()/scale;
sign = rand()%2;
number =  (sign == 1) ? base+fine/scale : -1*(base+fine/scale);
}
return number;
}
else
return number;
}
*/
