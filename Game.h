#pragma once
#include "SDL.h"
//#include "Texture.h"
#include "Tank.h"

class Game {
public:
	Game();
	~Game();
	bool Init();
	void Running();
	void Render();
	void Update(int sec);
	void Clean();
	void NewGame();

private:
	Tank * tank;
	SDL_Window * window;
	SDL_Renderer * renderer;
};