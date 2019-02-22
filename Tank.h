#pragma once
#include "Projectile.h"

class Tank : public GameTexture{
public:
	Tank(SDL_Renderer * renderer, double x, double y);
	~Tank();
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
	std::vector<Projectile*> projectiles;
	Uint32 sec;
	double cooldown;
};