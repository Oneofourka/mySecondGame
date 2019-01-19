#include "T34.h"

T34::T34(SDL_Renderer * renderer, double x, double y) : GameTexture(renderer, x, y) {
//	std::cout << "t34 constructor" << this << std::endl;
	SDL_Surface* surface = IMG_Load("images/t34.png");
	t34Texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	height = T34_HEIGHT;
	width = T34_WIDTH;
	cooldown = T34_COOLDOWN * FPS;
	sec = cooldown;
	angle = 180;
}

T34::~T34() {
//	std::cout << "t34 destructor" << this << std::endl;
	SDL_DestroyTexture(t34Texture);
}

void T34::Render() {
	SDL_Rect dstRect;

	dstRect.x = int(x);
	dstRect.y = int(y);
	dstRect.w = int(width);
	dstRect.h = int(height);

	SDL_RenderCopyEx(renderer, t34Texture, 0, &dstRect, angle, NULL, SDL_FLIP_NONE);
	for (size_t i = 0; i < projectiles.size(); ++i)
		projectiles[i]->Render();
}

void T34::Update() {
	++sec;
	Move();
	Shote();
	CleanProjectile();
}

void T34::Move() {
	int turnRand = rand() % 4;
//	std::cout << turnRand << std::endl;
	if (turnRand == 1)
		if (x <= 0)
			x = 0;
		else
		{
			angle = 270;
			turn = LEFT;
			x -= T34_SPEED;
		}
	else if (turnRand == 2)
		if (x + T34_WIDTH >= DISPLAY_WIDTH)
			x = DISPLAY_WIDTH - T34_WIDTH;
		else
		{
			angle = 90;
			turn = RIGHT;
			x += T34_SPEED;
		}
	else if (turnRand == 0)
		if (y <= -0.25 * T34_HEIGHT)
			y = -0.25 * T34_HEIGHT;
		else
		{
			angle = 0;
			turn = UP;
			y -= T34_SPEED;
		}
	else 
		if (y + 0.75 * T34_HEIGHT >= DISPLAY_HEIGHT)
			y = DISPLAY_HEIGHT - 0.75 * T34_HEIGHT;
		else
		{
			angle = 180;
			turn = DOWN;
			y += T34_SPEED;
		}
}

void T34::Shote()
{
	if (sec > cooldown)
	{
		if (turn == LEFT)
			projectiles.push_back(new Projectile(renderer, x - 0.5 * T34_WIDTH - 0.5 * PROJECTILE_HEIGHT, y + 0.5 * T34_HEIGHT - 0.5 * PROJECTILE_HEIGHT, turn));
		else if (turn == RIGHT)
			projectiles.push_back(new Projectile(renderer, x + 1.5 * T34_WIDTH + 0.25 * PROJECTILE_HEIGHT, y + 0.5 * T34_HEIGHT - 0.5 * PROJECTILE_HEIGHT, turn));
		else if (turn == UP)
			projectiles.push_back(new Projectile(renderer, x + 0.5 * T34_WIDTH - 0.5 * PROJECTILE_WIDTH, y - PROJECTILE_HEIGHT + 0.5 * PROJECTILE_WIDTH, turn));
		else
			projectiles.push_back(new Projectile(renderer, x + 0.5 * T34_WIDTH - 0.5 * PROJECTILE_WIDTH, y + T34_HEIGHT - 0.5 * PROJECTILE_WIDTH, turn));
		sec = 0;
	}
	for (size_t i = 0; i < projectiles.size(); ++i)
		projectiles[i]->Update();
}

void T34::CleanProjectile()
{
	for (size_t i = 0; i < projectiles.size(); ++i)
		if (projectiles[i]->getX() <= 0 || projectiles[i]->getX() >= DISPLAY_WIDTH || projectiles[i]->getY() <= 0 || projectiles[i]->getY() >= DISPLAY_HEIGHT)
		{
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i);
		}
}