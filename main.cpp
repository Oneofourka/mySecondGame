#include "Game.h"

int main(int argc, char *argv[]) {
	Game *game = new Game();

	if (game->Init())
	{
		game->Running();
	}
	delete game;
	return 0;
}