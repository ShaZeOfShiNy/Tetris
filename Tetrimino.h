
// The coordinates are from the origin point(the one in the middle
Coords SHAPES[7][4] =
{
	{ {-2, 0}, {-1, 0}, { 0, 0}, { 1, 0} }, // COLOR 0
	{ {-1, 1}, {-1, 0}, { 0, 0}, { 1, 0} }, // COLOR 1
	{ {-1, 0}, { 0, 0}, { 1, 0}, { 1, 1} }, // COLOR 2
	{ { 0, 0}, { 1, 0}, { 1, 1}, { 0, 1} }, // COLOR 3
	{ {-1, 0}, { 0, 0}, { 0, 1}, { 1, 1} }, // COLOR 4
	{ {-1, 0}, { 0, 0}, { 0, 1}, { 1, 0} }, // COLOR 5
	{ {-1, 1}, { 0, 1}, { 0, 0}, { 1, 0} }  // COLOR 6
};

Tetrimino::Tetrimino(GameField *a, int layout) {
	
	Coords x = a->getWidthHeight();
	SCREEN_WIDTH = x.x/2;
	SCREEN_HEIGHT = x.y;
//	color = getRandomColor();
	
	shapeIndex = color = getRandomColor();
	if(shapeIndex == 15) shapeIndex = 0;
	for(int i = 0; i < 4; i++)
		lastShape[i] = currentShape[i] = SHAPES[shapeIndex][i];
	
	currentPosition.x = SCREEN_WIDTH/2;
	currentPosition.y = 2;
	
	lastPosition = currentPosition;
}

Tetrimino::Tetrimino(GameField *a) {
	
	Coords x = a->getWidthHeight();
	SCREEN_WIDTH = x.x/2;
	SCREEN_HEIGHT = x.y;
	
	shapeIndex = color = getRandomColor();
	if(shapeIndex == 15) shapeIndex = 0;
	for(int i = 0; i < 4; i++)
		lastShape[i] = currentShape[i] = SHAPES[shapeIndex][i];
	
	currentPosition.x = SCREEN_WIDTH/2;
	currentPosition.y = 2;
	
	lastPosition = currentPosition;
}

void Tetrimino::getInfo(Coords* shape, Coords &position, int &color) {
	for(int i = 0; i < 4; i++)
		shape[i] = currentShape[i];
	
	position = currentPosition;
	color = this->color;
}

int Tetrimino::getRandomColor(void) {
//	return 15;
	int x = rand()%7;
	if(x == 0) x = 15;
	return x;
}
bool Tetrimino::rotateRight(void) {
	return rotate(true);
}
bool Tetrimino::rotateLeft(void) {
	return rotate(false);
}
bool Tetrimino::rotate(bool isRight) {
	
	// If it is a square you can't rotate it
	if(shapeIndex == 3) return false;
	
	Coords temp[4];
	
	for(int i = 0; i < 4; i++) {
		
		temp[i].x = currentShape[i].y * ((isRight)?-1: 1);
		temp[i].y = currentShape[i].x * ((isRight)? 1:-1);
	}
	
	if(!isPositionAcceptable(temp, currentPosition.x, currentPosition.y))
		return false;
	
	for(int i = 0; i < 4; i++) {
		lastShape[i] = currentShape[i];
		currentShape[i] = temp[i];
	}
	lastPosition = currentPosition;
	return true;
}

void Tetrimino::print(void) {
	
	textcolor(BLACK);
	for(int i = 0; i < 4; i++) {
		gotoxy((lastPosition.x+1)*2 + lastShape[i].x*2 + 1,
			   lastPosition.y + lastShape[i].y);
		printf("%c%c", 219, 219);
	}
	
	textcolor(color);
	for(int i = 0; i < 4; i++) {
		gotoxy((currentPosition.x+1)*2 + currentShape[i].x*2 + 1,
			   currentPosition.y + currentShape[i].y);
		printf("%c%c", 219, 219);
	}
}

void Tetrimino::getMinMax(Coords *shape, Coords &min, Coords &max) {
	min.x = 3; min.y = 3;
	max.x = -3; max.y = -3;
	for(int i = 0; i < 4; i++) {
		
		if(shape[i].x < min.x)
			min.x = shape[i].x;
		if(shape[i].x > max.x)
			max.x = shape[i].x;
		
		if(shape[i].y < min.y)
			min.y = shape[i].y;
		if(shape[i].y > max.y)
			max.y = shape[i].y;
	}
	return;
}

bool Tetrimino::isPositionAcceptable(Coords *shape, int x, int y) {
	
	Coords min, max;
	
	getMinMax(shape, min, max);
	
	if(x*2 + min.x*2 < 0					||
	   y*2 + min.y*2 <= 2					||
	   x*2 + max.x*2 > SCREEN_WIDTH*2-2 	||
	   y + max.y > SCREEN_HEIGHT + 1
		) return false;
	
	return true;
}

bool Tetrimino::moveLeft(void) {
	if(isPositionAcceptable(currentShape, currentPosition.x-1, currentPosition.y)) {
		for(int i = 0; i < 4; i++)
			lastShape[i] = currentShape[i];
		lastPosition = currentPosition;
		decrementX();
		return true;
	}
	return false;
}
bool Tetrimino::moveRight(void) {
	if(isPositionAcceptable(currentShape, currentPosition.x+1, currentPosition.y)) {
		for(int i = 0; i < 4; i++)
			lastShape[i] = currentShape[i];
		lastPosition = currentPosition;
		incrementX();
		return true;
	}
	return false;
}
bool Tetrimino::moveUp(void) {
	if(isPositionAcceptable(currentShape, currentPosition.x, currentPosition.y-1)) {
		for(int i = 0; i < 4; i++)
			lastShape[i] = currentShape[i];
		lastPosition = currentPosition;
		decrementY();
		return true;
	}
	return false;
}
bool Tetrimino::moveDown(void) {
	if(isPositionAcceptable(currentShape, currentPosition.x, currentPosition.y+1)) {
		for(int i = 0; i < 4; i++)
			lastShape[i] = currentShape[i];
		lastPosition = currentPosition;
		incrementY();
		return true;
	}
	return false;
}

void Tetrimino::decrementY(void) { currentPosition.y--; }
void Tetrimino::incrementY(void) { currentPosition.y++; }
void Tetrimino::decrementX(void) { currentPosition.x--; }
void Tetrimino::incrementX(void) { currentPosition.x++; }
