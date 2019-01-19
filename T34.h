#pragma once
#include "GameTexture.h"
#include "Projectile.h"
#include <vector>

class T34 : public GameTexture {
public:
	T34(SDL_Renderer * renderer, double x, double y);
	~T34() override;
	void Render();
	void Update();
	void Move();
	void Shote();
	void CleanProjectile();

private:
	SDL_Texture * t34Texture;
	std::vector<Projectile*> projectiles;
	Uint32 sec;
	double cooldown;
};