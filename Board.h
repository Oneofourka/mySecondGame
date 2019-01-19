#pragma once
#include "GameTexture.h"
#include <vector>
#include "Brick.h"
#include <fstream>
#include <string>

class Board{
public:
	Board(SDL_Renderer * renderer);
	~Board();
	void Render();
private:
	SDL_Renderer * renderer;
	std::vector<std::string> mapVector;
	std::vector<Brick*> bricksVector;
};