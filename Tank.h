#pragma once
#include "GameTexture.h"
#include "Projectile.h"
#include <vector>

class Tank : public GameTexture {
public:
	Tank(SDL_Renderer * renderer, double x, double y);
	~Tank() override;
	void Render();
	void Update();
	void Move();
	void Shote();
	void CleanProjectile();

private:
	SDL_Texture * tankTexture;
	std::vector<Projectile*> projectiles;
	Uint32 sec;
	double cooldown;
};