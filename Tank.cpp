#include "Tank.h"

Tank::Tank(SDL_Renderer * renderer, double x, double y) : GameTexture(renderer, x, y) {
	SDL_Surface* surface = IMG_Load("images/tiger.png");
	tankTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	height = TIGER_HEIGHT;
	width = TIGER_WIDTH;
	cooldown = TIGER_COOLDOWN * FPS;
	sec = cooldown;
}

Tank::~Tank() {

}

void Tank::Render() {
	dstRect.x = int(x);
	dstRect.y = int(y);
	dstRect.w = int(width);
	dstRect.h = int(height);
}

void Tank::Update() {
	++sec;
	Move();
	Shote();
	for (size_t i = 0; i < projectiles.size(); ++i)
		if (projectiles[i]->getX() <= 0 || projectiles[i]->getX() >= DISPLAY_WIDTH || projectiles[i]->getY() <= 0 || projectiles[i]->getY() >= DISPLAY_HEIGHT)
			CleanProjectile(i);
}

void Tank::Move() {
	const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[SDL_SCANCODE_LEFT])
		if (x <= 0)
			x = 0;
		else
		{
			angle = 270;
			turn = LEFT;
			x -= TIGER_SPEED;
		}
	else if (keyboardState[SDL_SCANCODE_RIGHT])
		if (x + TIGER_WIDTH >= DISPLAY_WIDTH)
			x = DISPLAY_WIDTH - TIGER_WIDTH;
		else
		{
			angle = 90;
			turn = RIGHT;
			x += TIGER_SPEED;
		}
	else if (keyboardState[SDL_SCANCODE_UP])
		if (y <= -0.25 * TIGER_HEIGHT)
			y = -0.25 * TIGER_HEIGHT;
		else
		{
			angle = 0;
			turn = UP;
			y -= TIGER_SPEED;
		}
	else if (keyboardState[SDL_SCANCODE_DOWN])
		if (y + 0.75 * TIGER_HEIGHT >= DISPLAY_HEIGHT)
			y = DISPLAY_HEIGHT - 0.75 * TIGER_HEIGHT;
		else
		{
			angle = 180;
			turn = DOWN;
			y += TIGER_SPEED;
		}
	if (keyboardState[SDL_SCANCODE_SPACE] && sec > cooldown)
	{
		if (turn == LEFT)
			projectiles.push_back(new Projectile(renderer, x + 0.5 * PROJECTILE_HEIGHT, y + 0.5 * TIGER_HEIGHT - 0.5 * PROJECTILE_HEIGHT, turn));
		else if (turn == RIGHT)
			projectiles.push_back(new Projectile(renderer, x + TIGER_WIDTH - 0.5 * PROJECTILE_HEIGHT, y + 0.5 * TIGER_HEIGHT - 0.5 * PROJECTILE_HEIGHT, turn));
		else if (turn == UP)
			projectiles.push_back(new Projectile(renderer, x + 0.5 * TIGER_WIDTH - 0.5 * PROJECTILE_WIDTH, y + 0.25 * TIGER_HEIGHT, turn));
		else
			projectiles.push_back(new Projectile(renderer, x + 0.5 * TIGER_WIDTH - 0.5 * PROJECTILE_WIDTH, y + 0.5 * TIGER_HEIGHT, turn));
		sec = 0;
	}
}

void Tank::Shote()
{
	for (size_t i = 0; i < projectiles.size(); ++i)
		projectiles[i]->Update();
}

void Tank::CleanProjectile(size_t i)
{
	delete projectiles[i];
	projectiles.erase(projectiles.begin() + i);
}

double Tank::getXProjectile(size_t i) {
	return projectiles[i]->getX();
}

double Tank::getYProjectile(size_t i) {
	return projectiles[i]->getY();
}

size_t Tank::getProjectileSize() {
	return projectiles.size();
}

Turn Tank::getProjectileTurn(size_t i) {
	return projectiles[i]->GetTurn();
}

int Tank::getProjectileWidth(size_t i) {
	return projectiles[i]->getWidth();
}

int Tank::getProjectileHeight(size_t i) {
	return projectiles[i]->getHeight();
}