#include "Tetris.h"

Peace::Peace(){
	//Create the first peace
	iniPoint.y = 1;
	iniPoint.x = 5;
	int randNum = rand() % 7;
	for (int i = 0; i < PARTSELEM; ++i){
		TempPart[i].x = iniPart[randNum][i].x + iniPoint.x;
		TempPart[i].y = iniPart[randNum][i].y + iniPoint.y;
	}
}
//Rotate the current piece, check for collisions and correct the peace's place if it colides with any of the sides
void Peace::RotatePeace() {
	coords Temp[PARTSELEM];
	coords RotateOffset;
	char correction = 0;
	bool rotate = true;

	RotateOffset.x = iniPoint.x + iniPoint.y;
	RotateOffset.y = iniPoint.y - iniPoint.x;

	//rotate the indexes
	for (int i = 0; i < PARTSELEM; i++){
		Temp[i].x = -1 * TempPart[i].y + RotateOffset.x;
		Temp[i].y = TempPart[i].x + RotateOffset.y;
		//Temp[i].x = -1 * TempPart[i].y;
		//Temp[i].y = TempPart[i].x;
	}

	//check for side collisions and find the correction
	for (int i = 0; i < PARTSELEM; i++){
		if (Temp[i].x <= 0){
			correction = 1 - MinElem(Temp);
		}
		if (Temp[i].x >= WIDTH){
			correction = (WIDTH - 1) - MaxElem(Temp);
		}
	}

	//move the peace according to the correction
	for (int i = 0; i < PARTSELEM; i++)
		Temp[i].x = Temp[i].x + correction;

	//checks for any surroundings from the board
	for (int i = 0; i < PARTSELEM; i++)
	if (BoardArr[Temp[i].y][Temp[i].x] == 1)
		rotate = false;

	//if all checks are completed add the indexes of the new piece and display the peace
	if (rotate){
		//update the indexes in the current pieace
		for (int i = 0; i < PARTSELEM; i++){
			TempPart[i].x = Temp[i].x;
			TempPart[i].y = Temp[i].y;
		}
		//display the peace on the board
		DisplayPeace(TempPart);
	}
}

//Find the biggest X from peace on the board
char Peace::MaxElem(coords peace[PARTSELEM]){
	char max = peace[0].x;

	for (int i = 0; i < PARTSELEM; i++)
	if (peace[i].x > max)
		max = peace[i].x;

	return max;
}

//Find the smallest X from peace on the board
char Peace::MinElem(coords peace[PARTSELEM]){
	char min = peace[0].x;

	for (int i = 0; i < PARTSELEM; i++)
	if (peace[i].x < min)
		min = peace[i].x;

	return min;
}

//Delete peace from the board
void Peace::DeletePeace(coords peace[PARTSELEM]){

	for (int i = 0; i < PARTSELEM; i++)
		BoardArr[peace[i].y][peace[i].x] = 0;
}

//Display (hardcode) peace on the board
void Peace::DisplayPeace(coords peace[PARTSELEM]){

	for (int i = 0; i < PARTSELEM; i++)
		BoardArr[peace[i].y][peace[i].x] = 1;
}

void Peace::PeaceAssign(char offsetY, char offsetX){

	for (int i = 0; i < PARTSELEM; i++){
		TempPart[i].x = TempPart[i].x + offsetX;
		TempPart[i].y = TempPart[i].y + offsetY;
	}
}

//Checks for collisions with the left of right sides of the board or with the other pieaces that are already on the board
bool Peace::CollisionDetection(coords peace[PARTSELEM], char iniY, char iniX){
	coords Temp[PARTSELEM];
	bool collision = false;

	//find the new coords after move on X or on Y
	for (int i = 0; i < PARTSELEM; i++){
		Temp[i].x = peace[i].x + iniX;
		Temp[i].y = peace[i].y + iniY;
	}

	//Check for collision with the sides of the board
	for (int i = 0; i < PARTSELEM; i++){
		if (Temp[i].x <= 0 || Temp[i].x >= WIDTH){
			collision = true;
		}

		//Check from collisions with other peaces on the board
		for (int i = 0; i < PARTSELEM; i++)
		if (BoardArr[Temp[i].y][Temp[i].x] == 1)
			collision = true;
	}

	return collision;
};

/*
void Peace::IndexToArrTransform(coords parts[PARTSELEM], int offset_y, int offset_x){
for (int i = 0; i < PARTSELEM; ++i){
parts[i].y = parts[i].y + offset_y;
parts[i].x = parts[i].x + offset_x;
}

for (int i = 0; i < PARTSELEM; i++){
for (int j = 0; j < PARTSELEM; j++){
for (int k = 0; k < PARTSELEM; k++){
if (parts[k].y == i && parts[k].x == j){
NextPartDisplayArr[i][j] = 1;
break;
}
else NextPartDisplayArr[i][j] = 0;
}
}
}
}
*/

void Peace::KeyInput(){
	if (_kbhit()){
		switch (_getch())
		{
			//Move Left
		case 97:
			DeletePeace(TempPart);
			if (!CollisionDetection(TempPart, 0, -1)){
				iniPoint.x--;
				PeaceAssign(0, -1);
			}
			DisplayPeace(TempPart);
			break;
			//Move Up (rotate)
		case 119:
			DeletePeace(TempPart);
			RotatePeace();
			DisplayPeace(TempPart);
			break;
			//Move down
		case 115:
			DeletePeace(TempPart);
			if (!CollisionDetection(TempPart, 1, 0)){
				iniPoint.y++;
				PeaceAssign(1, 0);
				DisplayPeace(TempPart);
			}
			else {
				newBoard.setNextPeace(true);
				DisplayPeace(TempPart);
			}
			break;
			//Move Right
		case 100:
			DeletePeace(TempPart);
			if (!CollisionDetection(TempPart, 0, 1)){
				iniPoint.x++;
				PeaceAssign(0, 1);
			}
			DisplayPeace(TempPart);
			break;
			//Hit spacebar
		case 32:
			DeletePeace(TempPart);
			while (!CollisionDetection(TempPart, 1, 0)){
				iniPoint.y++;
				PeaceAssign(1, 0);
			}
			newBoard.setNextPeace(true);
			DisplayPeace(TempPart);
			break;
		}
	}
}

void Peace::CreateNextPeace(){
	int randNum_next = rand() % 7;
	for (int i = 0; i < PARTSELEM; ++i){
		NextPart[i].x = iniPart[randNum_next][i].x + iniPoint.x;
		NextPart[i].y = iniPart[randNum_next][i].y + iniPoint.y;
		NextPartDisplay[i].x = iniPart[randNum_next][i].x + X_NEXT_INIT;
		NextPartDisplay[i].y = iniPart[randNum_next][i].y + Y_NEXT_INIT;
	}
}

void Peace::CopyNextToCurrentPeace(){
	for (int i = 0; i < PARTSELEM; i++)
		TempPart[i] = NextPart[i];
}
