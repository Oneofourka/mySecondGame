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
	void CleanProjectile(size_t i);
	double getXProjectile(size_t i);
	double getYProjectile(size_t i);
	size_t getProjectileSize();
	Turn getProjectileTurn(size_t i);
	int getProjectileWidth(size_t i);
	int getProjectileHeight(size_t i);

private:
	SDL_Texture * tigerTexture;
	std::vector<Projectile*> projectiles;
	Uint32 sec;
	double cooldown;
};