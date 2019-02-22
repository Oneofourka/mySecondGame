#include "Board.h"

Board::Board(SDL_Renderer * renderer){
	this->renderer = renderer;
	std::string map = "lvl/map.txt";
	std::fstream fs;
	fs.open(map, std::fstream::in);

	if (!fs.is_open())
		std::cout << "Error opening file" << std::endl;
	else
		while (!fs.eof())
		{
			std::string str;
			std::getline(fs, str);
			if (str != "\0")
				mapVector.push_back(str);
		}
	fs.close();
	int y = 0;
	for (std::string str : mapVector)
	{
		int x = 0;
		for (size_t i = 0; i < str.size(); ++i)
		{
			if (str[i] == '1')
			{
				bricksVector.push_back(new Brick(renderer, x, y, FULL_BRICK));
				x += BRICK_WIDTH;
			}
			else if (str[i] == '2')
			{
				bricksVector.push_back(new Brick(renderer, x, y, UP_BRICK));
				x += BRICK_WIDTH;
			}
			else if (str[i] == '3')
			{
				bricksVector.push_back(new Brick(renderer, x, y, LEFT_BRICK));
				x += BRICK_WIDTH;
			}
			else if (str[i] == '4')
			{
				bricksVector.push_back(new Brick(renderer, x, y, RIGHT_BRICK));
				x += BRICK_WIDTH;
			}
			else if (str[i] == '5')
			{
				bricksVector.push_back(new Brick(renderer, x, y, DOWN_BRICK));
				x += BRICK_WIDTH;
			}
		}
		y += BRICK_HEIGHT;
	}
//	std::cout << "board constructor " << this << std::endl;
}

Board::~Board() {
//	std::cout << "board destructor " << this << std::endl;
}

void Board::Render() {
	for (size_t i = 0; i < bricksVector.size(); ++i)
		bricksVector[i]->Render();
}

void Board::Clean() {
	for (size_t i = 0; i < bricksVector.size(); ++i)
		delete bricksVector[i];
	bricksVector.clear();
}

size_t Board::getBrickSize() {
	return bricksVector.size();
}

Brick * Board::getBrick(size_t i) {
	return bricksVector[i];
}

void Board::DeleteBrick(size_t i, BrickType temp) {
	if (getBrick(i)->getBrickType() == FULL_BRICK) 
	{
		double tempX = getBrick(i)->getX();
		double tempY = getBrick(i)->getY();
		delete bricksVector[i];
		bricksVector.erase(bricksVector.begin() + i);
		if (temp == UP_BRICK)
			bricksVector.push_back(new Brick(renderer, tempX, tempY, UP_BRICK));
		else if (temp == LEFT_BRICK) 
			bricksVector.push_back(new Brick(renderer, tempX, tempY, LEFT_BRICK));
		else if (temp == RIGHT_BRICK)
			bricksVector.push_back(new Brick(renderer, tempX, tempY, RIGHT_BRICK));
		else if (temp == DOWN_BRICK)
			bricksVector.push_back(new Brick(renderer, tempX, tempY, DOWN_BRICK));
	}
	else {
		delete bricksVector[i];
		bricksVector.erase(bricksVector.begin() + i);
	}
}