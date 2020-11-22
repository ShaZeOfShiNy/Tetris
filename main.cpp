/*
	Made by: Matteo Galletta
	
	on day: 22/11/2020
	
	Tetris
	
	Version: v1.0
	
	TODO:
		-Add Score
		-Add Commands
		-Add Menu
		-End the game when the blocks are too high
		-[BUG] When moving left or right you can go into the other blocks
*/
// https://bit.ly/2Uw5x41
// When GameField color is equal to minus one, it means no block is there

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <conio2.h>
#include <time.h>
#include <windows.h>

// Macros just used in the main functions
#define GAMEFIELD_WIDTH 10
#define GAMEFIELD_HEIGHT 20
#define FALL_IN_SECONDS 1

struct Coords {
	int x, y;
};
class Tetrimino;
class GameField {
	public:
		GameField(void);
		GameField(int x, int y);
		~GameField(void);
		void print(void);
		
		void addTetrimino(Tetrimino *tetrimino);
		bool mustTetriminoStop(Tetrimino *tetrimino);
		
		Coords getWidthHeight(void);
	private:
		void checkFullRow(int rowIndex);
		void initializeGrid(void);
		void setColor(int x, int y);
		int **grid;
	protected:
		int width;
		int height;
};
class Tetrimino {
	public:
		Tetrimino(GameField *a, int shape);
		Tetrimino(GameField *a);
		void print(void);
		
		bool rotateRight(void);
		bool rotateLeft(void);
		bool moveLeft(void);
		bool moveRight(void);
		bool moveUp(void); // not used
		bool moveDown(void);
		
		bool isPositionAcceptable(Coords *shape, int x, int y);
		
		void getInfo(Coords* shape, Coords &position, int &color);
	private:
		void getMinMax(Coords *shape, Coords &min, Coords &max);
		bool rotate(bool isRight);
		
		void decrementY(void);
		void incrementY(void);
		void decrementX(void);
		void incrementX(void);
		
		int getRandomColor(void);
		
		Coords topLeft;
		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
	protected:
		int color, shapeIndex;
		Coords currentShape[4];
		Coords currentPosition;
		Coords lastShape[4];
		Coords lastPosition;
};
#include "GameField.h"
#include "Tetrimino.h"
#include "Timer.h"

bool getAndElaborateInput(Tetrimino *tetrimino, Timer *timer);
void hideConsoleCursor(void);
void addToFieldAndCreateNewTetrimino(Tetrimino **tetrimino, GameField *gameField);

int main(void) {
	srand(time(NULL));
	
	hideConsoleCursor();
	
	GameField gameField(2*GAMEFIELD_WIDTH, GAMEFIELD_HEIGHT); gameField.print();
	
	Tetrimino *tetrimino = new Tetrimino(&gameField); tetrimino->print();
	
	Timer timer(FALL_IN_SECONDS); // the timer starts here and lastes <FALL_IN_SECONDS> seconds
	
	bool gameRunning = true;
	while(gameRunning) {
		
		if(!(kbhit() || timer.isTimeElapsed())) continue;
		
		if(getAndElaborateInput(tetrimino, &timer))
			tetrimino->print();
		
		if(gameField.mustTetriminoStop(tetrimino))
			addToFieldAndCreateNewTetrimino(&tetrimino, &gameField);
		
		timer.start(FALL_IN_SECONDS);
	}
	
	getch(); system("CLS");
	textcolor(WHITE); textbackground(BLACK);
	gotoxy(1, 1); puts("Thanks for playing.");
	getch(); system("CLS");
	return 0;
}

void addToFieldAndCreateNewTetrimino(Tetrimino **tetrimino, GameField *gameField) {
//	(*tetrimino)->moveUp();
	gameField->addTetrimino(*tetrimino);
	gameField->print();
	delete *tetrimino;
	*tetrimino = new Tetrimino(gameField);
	(*tetrimino)->print();
}

bool getAndElaborateInput(Tetrimino* tetrimino, Timer *timer) {
	
	unsigned char input;
	if(timer->isTimeElapsed()) return tetrimino->moveDown();
	else input = getch();
	
	if(input >= 'a' && input <= 'z')
		input -= 'a' - 'A';
	
	switch(input) {
		
		case 'A':
			return tetrimino->moveLeft();
		case 'D':
			return tetrimino->moveRight();
		case 'S':
			return tetrimino->moveDown();
		case 'Q':
			return tetrimino->rotateLeft();
		case 'E':
			return tetrimino->rotateRight();
	}
	
	return false;
}

void hideConsoleCursor(void) {
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

