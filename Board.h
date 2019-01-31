#pragma once
#include "Texture.h"
#include <vector>
#include "Brick.h"
#include <fstream>
#include <string>

class Board{
public:
	Board(SDL_Renderer * renderer);
	~Board();
	void Render();
	void Clean();
	size_t getBrickSize();
	Brick * getBrick(size_t i);
	void DeleteBrick(size_t i, BrickType temp);

private:
	SDL_Renderer * renderer;
	std::vector<std::string> mapVector;
	std::vector<Brick*> bricksVector;
};