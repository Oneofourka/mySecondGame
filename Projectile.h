#pragma once
#include "GameTexture.h"

class Projectile : public GameTexture {
public:
	Projectile(SDL_Renderer * renderer, double x, double y, Turn turn);
	~Projectile() override;
	void Render();
	void Update();
	void Move();
//	int getProjectileWidth();
//	int getProjectileHeight();

private:
	SDL_Texture * projectileTexture;
};