#include "Game.h"
#include <iostream>

Game::Game() {
//	std::cout << "game constructor" << this << std::endl;
	window = nullptr;
	renderer = nullptr;
}

Game::~Game() {
//	std::cout << "game destructor" << this << std::endl;
	Clean();
}

bool Game::Init() {
	SDL_DisplayMode displayMode;
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)		//initialization of all subsystems
	{
		int request = SDL_GetDesktopDisplayMode(0, &displayMode);
		window = SDL_CreateWindow("Tanks 0.01", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DISPLAY_WIDTH, DISPLAY_HEIGHT, false);
		//window = SDL_CreateWindow("Tanks 0.01", 0, 0, displayMode.w, displayMode.h, SDL_WINDOW_SHOWN);	//false - fullscreen
		if (!window)
		{
			SDL_Log("Unable to window SDL: %s", SDL_GetError());
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, 0);
			//renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);	//-1 for single window, flag = 0;
			if (renderer)
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //r, g, b, alfa;
			else
			{
				SDL_Log("Unable to render SDL: %s", SDL_GetError());
				success = false;
			}
		}
	}
	else
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		success = false;
	}
	return success;
}

void Game::Running() {
	NewGame();
	Uint32 frameStart;
	int frameTime;
	
	bool exit = true;
	while(exit)
	{
		frameStart = SDL_GetTicks();
	
		SDL_Event event;
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT)
				exit = false;

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(Uint32(frameDelay - frameTime));
		Render();

		Update();
	}
}

void Game::Render() {
	SDL_RenderClear(renderer);
	tank->Render();
	SDL_RenderPresent(renderer);
}

void Game::Update() {
	tank->Update();
}

void Game::Clean() {
	delete tank;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::NewGame() {
	tank = new Tank(renderer, DISPLAY_WIDTH / 2.0 - TANK_WIDTH / 2.0, DISPLAY_HEIGHT - TANK_HEIGHT);
}