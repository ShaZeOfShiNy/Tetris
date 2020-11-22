
GameField::GameField(void) {
	this->width = 20;
	this->height = 10;
	
	initializeGrid();
}

GameField::GameField(int width, int height) {
	this->width = width;
	this->height = height;
	
	initializeGrid();
}

GameField::~GameField(void) {
	delete grid;
}

bool GameField::mustTetriminoStop(Tetrimino *tetrimino) {
	
	Coords shape[4];
	
	Coords position; int color;
	tetrimino->getInfo(shape, position, color);
	
	if(!tetrimino->isPositionAcceptable(shape, position.x, position.y + 1))
		return true;
	
	int x, y;
	for(int i = 0; i < 4; i++) {
		x = position.x + shape[i].x;
		y = position.y + shape[i].y - 1;
		if(x < 0 || x >= width || y < 0 || y >= height ) return false;
		if(grid[x][y] != -1) return true;
	}
	return false;
}

void GameField::addTetrimino(Tetrimino *tetrimino) {
	
	Coords *shape = (Coords *) malloc(sizeof(Coords) * 4);
	if(shape == NULL) exit(2);
	
	Coords position; int color;
	tetrimino->getInfo(shape, position, color);
	
	textcolor(WHITE);
	for(int i = 0; i < 4; i++) {
		grid[ position.x + shape[i].x]
			[ position.y + shape[i].y - 2]
			  = color;
	}
	
	for(int i = 0; i < 4; i++)
		checkFullRow(position.y + shape[i].y - 2);
	
	free(shape);
}

void GameField::checkFullRow(int rowIndex) {
	
	for(int i = 0; i < height; i++)
		if(grid[i][rowIndex] == -1)
			return;
	
	for(int i = 0; i < width; i++)
		for(int j = rowIndex; j >= 1; j--)
			grid[i][j] = grid[i][j - 1];
	
}

void GameField::initializeGrid(void) {
	grid = (int **)malloc(sizeof(int) * width);
	for(int i = 0; i < width; i++)
		grid[i] = (int *)malloc(sizeof(int) * height);
	
	for(int i = 0; i < width/2; i++)
		for(int j = 0; j < height; j++)
			grid[i][j] = -1;
}

Coords GameField::getWidthHeight(void) {
	Coords a;
	a.x = width; a.y = height;
	return a;
}

void GameField::setColor(int x, int y) {
	int color;
	if(grid[x][y] >= 1 && grid[x][y] <= 6) color = grid[x][y];
	else if(grid[x][y] == -1) color = BLACK;
	else color = WHITE;
	
	textcolor(color);
}

void GameField::print(void) {
	textcolor(WHITE);
	// LEFT SIDE
	for(int i = 0; i < height + 2; i++) {
		gotoxy(1, i + 1);
		printf("%c", 219);
	}
	for(int i = 0; i < height + 2; i++) {
		gotoxy(2, i + 1);
		printf("%c", 219);
	}
	
	// RIGHT SIDE
	for(int i = 0; i < height + 2; i++) {
		gotoxy(width + 3, i + 1);
		printf("%c", 219);
	}
	for(int i = 0; i < height + 2; i++) {
		gotoxy(width + 4, i + 1);
		printf("%c", 219);
	}
	
	// TOP SIDE
	for(int i = 0; i < width; i++) {
		gotoxy(i + 3, 1);
		printf("%c", 219);
	}
	
	// BOTTOM SIDE
	for(int i = 0; i < width; i++) {
		gotoxy(i + 3, height + 2);
		printf("%c", 219);
	}
	
	// Prints the tetriminos on the board
	for(int i = 0; i < width/2; i++)
		for(int j = 0; j < height; j++) {
			gotoxy(2*i + 3, j + 2);
			setColor(i, j);
			printf("%c%c", 219, 219);
			textcolor(WHITE);
		}
}

