#pragma once
#include "Texture.h"

enum BrickType {
	FULL_BRICK,
	UP_BRICK,
	LEFT_BRICK,
	RIGHT_BRICK,
	DOWN_BRICK
};

class Brick : public Texture {
public:
	Brick(SDL_Renderer * renderer, double x, double y, BrickType type);
	~Brick() override;
	void Render();
	BrickType getBrickType();

private:
	BrickType type;
};