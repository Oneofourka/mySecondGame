#pragma once
#include "Texture.h"
#include <vector>
#include <string>

enum Turn {
	UP,
	LEFT,
	RIGHT,
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