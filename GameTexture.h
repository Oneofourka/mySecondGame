#pragma once
#include "Texture.h"
#include <vector>

enum Turn {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class GameTexture : public Texture {
public:
	GameTexture(SDL_Renderer * renderer, double x, double y);
	~GameTexture() override;
	Turn GetTurn();
	void SetTurn(Turn turn);

protected:
	SDL_Texture * gameTexture;
	int angle;
	Turn turn;
};