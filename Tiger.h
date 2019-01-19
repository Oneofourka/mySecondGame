#pragma once
#include "GameTexture.h"
#include "Projectile.h"
#include <vector>

class Tiger : public GameTexture {
public:
	Tiger(SDL_Renderer * renderer, double x, double y);
	~Tiger() override;
	void Render();
	void Update();
	void Move();
	void Shote();
	void CleanProjectile();

private:
	SDL_Texture * tigerTexture;
	std::vector<Projectile*> projectiles;
	Uint32 sec;
	double cooldown;
};