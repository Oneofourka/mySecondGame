#pragma once
#include "Texture.h"

class Brick : public Texture {
public:
	Brick(SDL_Renderer * renderer, double x, double y);
	~Brick() override;
	void Render();
	void Update();

private:
	SDL_Texture * brickTexture;
};