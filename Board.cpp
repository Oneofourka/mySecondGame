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
				bricksVector.push_back(new Brick(renderer, x, y));
				x += BRICK_WIDTH;
			}
		}
		y += BRICK_HEIGHT;
	}
	std::cout << "board constructor " << this << std::endl;

}

Board::~Board() {
	std::cout << "board destructor " << this << std::endl;
}

void Board::Render() {
	for (size_t i = 0; bricksVector.size(); ++i)
		bricksVector[i]->Render();
}