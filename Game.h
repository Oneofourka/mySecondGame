#pragma once
#include "SDL.h"
#include "Tiger.h"
#include "T34.h"
#include <ctime>
#include "Board.h"

class Game {
public:
	Game();
	~Game();
	bool Init();
	void Running();
	void Render();
	void Update();
	void Clean();
	void NewGame();
	void BrickCollisionProjectile();
	void BrickCollisionTank();

private:
	std::vector <T34*> bots;
	Tiger * firstPlayer;
	Board * board;
	SDL_Window * window;
	SDL_Renderer * renderer;
};