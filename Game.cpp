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
	srand(time(NULL));
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
	firstPlayer->Render();
	for (size_t i = 0; i < bots.size(); ++i)
		bots[i]->Render();
	board->Render();
	SDL_RenderPresent(renderer);
}

void Game::Update() {
	firstPlayer->Update();
	for (size_t i = 0; i < bots.size(); ++i)
		bots[i]->Update();
	BrickCollisionProjectile();
	BrickCollisionTank();
}

void Game::Clean() {
	for (size_t i = 0; i < bots.size(); ++i)
		delete bots[i];
	bots.clear();
	board->Clean();
	delete board;
	delete firstPlayer;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::NewGame() {
	board = new Board(renderer);
	//firstPlayer = new Tiger(renderer, DISPLAY_WIDTH / 2.0 - TIGER_WIDTH / 2.0, DISPLAY_HEIGHT - TIGER_HEIGHT);
	firstPlayer = new Tiger(renderer, DISPLAY_WIDTH / 2.0 - TIGER_WIDTH / 2.0, DISPLAY_HEIGHT - TIGER_HEIGHT - 100);
	int x = 0;
	for (size_t i = 0; i < 5; ++i)
	{
		bots.push_back(new T34(renderer, x, 0));
		x += 2 * T34_WIDTH;
	}
}

void Game::BrickCollisionProjectile() {
	for (size_t i = 0; i < firstPlayer->getProjectileSize(); ++i){
		for (size_t j = 0; j < board->getSize(); ++j) {
			if (firstPlayer->getProjectileTurn(i) == UP && firstPlayer->getYProjectile(i) <= board->getBrick(j)->getY() + board->getBrick(j)->getHeight() && firstPlayer->getYProjectile(i) > board->getBrick(j)->getY()
				&& firstPlayer->getXProjectile(i) + firstPlayer->getProjectileWidth(i) / 2.0 >= board->getBrick(j)->getX() && firstPlayer->getXProjectile(i) + firstPlayer->getProjectileWidth(i) / 2.0 <= board->getBrick(j)->getX() + board->getBrick(j)->getWidth())
			{
				board->DeleteBrick(j, UP_BRICK);
				firstPlayer->CleanProjectile(i);
				break;
			}
			else if (firstPlayer->getProjectileTurn(i) == LEFT && firstPlayer->getXProjectile(i) <= board->getBrick(j)->getX() + board->getBrick(j)->getWidth() && firstPlayer->getXProjectile(i) > board->getBrick(j)->getX()
				&& firstPlayer->getYProjectile(i) + firstPlayer->getProjectileHeight(i) * 0.5 >= board->getBrick(j)->getY() && firstPlayer->getYProjectile(i) + firstPlayer->getProjectileHeight(i) * 0.5 <= board->getBrick(j)->getY() + board->getBrick(j)->getHeight())
			{
				board->DeleteBrick(j, LEFT_BRICK);
				firstPlayer->CleanProjectile(i);
				break;
			}
			else if (firstPlayer->getProjectileTurn(i) == RIGHT && firstPlayer->getXProjectile(i) >= board->getBrick(j)->getX() && firstPlayer->getXProjectile(i) < board->getBrick(j)->getX() + board->getBrick(j)->getHeight()
				&& firstPlayer->getYProjectile(i) + firstPlayer->getProjectileHeight(i) * 0.5 >= board->getBrick(j)->getY() && firstPlayer->getYProjectile(i) + firstPlayer->getProjectileHeight(i) * 0.5 <= board->getBrick(j)->getY() + board->getBrick(j)->getHeight())
			{
				board->DeleteBrick(j, RIGHT_BRICK);
				firstPlayer->CleanProjectile(i);
				break;
			}
			else if (firstPlayer->getProjectileTurn(i) == DOWN && firstPlayer->getYProjectile(i) + firstPlayer->getProjectileHeight(i) >= board->getBrick(j)->getY() && firstPlayer->getYProjectile(i) < board->getBrick(j)->getY()
				&& firstPlayer->getXProjectile(i) + firstPlayer->getProjectileWidth(i) / 2.0 >= board->getBrick(j)->getX() && firstPlayer->getXProjectile(i) + firstPlayer->getProjectileWidth(i) / 2.0 <= board->getBrick(j)->getX() + board->getBrick(j)->getWidth())
			{
				board->DeleteBrick(j, DOWN_BRICK);
				firstPlayer->CleanProjectile(i);
				break;
			}
		}
	}
}

void Game::BrickCollisionTank() {
/*	for (size_t i = 0; i < board->getBrickSize(); ++i)
	{
		if (firstPlayer->GetTurn() == UP && firstPlayer->getY() <= board->getBrick(i)->getY() + board->getBrick(i)->getHeight() * 0.75 && board->getBrick(i)->getX())
			firstPlayer->setY(board->getBrick(i)->getY() + board->getBrick(i)->getHeight() * 0.75);
		else if (firstPlayer->GetTurn() == LEFT && firstPlayer->getX() <= board->getBrick(i)->getX() + board->getBrick(i)->getWidth())
			std::cout << "2" << std::endl;
		else if (firstPlayer->GetTurn() == RIGHT && firstPlayer->getX() + firstPlayer->getWidth() >= board->getBrick(i)->getX())
			std::cout << "3" << std::endl;
		else if (firstPlayer->GetTurn() == DOWN && firstPlayer->getY() + firstPlayer->getHeight() >= board->getBrick(i)->getY())
			std::cout << "4" << std::endl;
	}*/
}