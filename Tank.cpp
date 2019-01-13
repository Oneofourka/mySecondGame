#include "Tank.h"

Tank::Tank(SDL_Renderer * renderer, double x, double y) : GameTexture(renderer, x, y) {
	//	std::cout << "tank constructor" << this << std::endl;
	SDL_Surface* surface = IMG_Load("images/tank.png");
	tankTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	height = TANK_HEIGHT;
	width = TANK_WIDTH;
	cooldown = TANK_COOLDOWN * FPS;
	sec = 0;
}

Tank::~Tank() {
	//	std::cout << "tank destructor" << this << std::endl;
	SDL_DestroyTexture(tankTexture);
}

void Tank::Render() {
	SDL_Rect dstRect;

	dstRect.x = int(x);
	dstRect.y = int(y);
	dstRect.w = int(width);
	dstRect.h = int(height);

	SDL_RenderCopyEx(renderer, tankTexture, 0, &dstRect, angle, NULL, SDL_FLIP_NONE);
	for (size_t i = 0; i < projectiles.size(); ++i)
		projectiles[i]->Render();
}

void Tank::Update() {
	++sec;
	std::cout << sec << std::endl;
	Move();
	Shote();
//	std::cout << projectiles.size() << std::endl;
	CleanProjectile();
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
			x -= TANK_SPEED;
		}
	else if (keyboardState[SDL_SCANCODE_RIGHT])
		if (x + TANK_WIDTH >= DISPLAY_WIDTH)
			x = DISPLAY_WIDTH - TANK_WIDTH;
		else
		{
			angle = 90;
			turn = RIGHT;
			x += TANK_SPEED;	
		}
	else if (keyboardState[SDL_SCANCODE_UP])
		if (y <= -0.25 * TANK_HEIGHT)
			y = -0.25 * TANK_HEIGHT;
		else
		{
			angle = 0;
			turn = UP;
			y -= TANK_SPEED;
		}
	else if (keyboardState[SDL_SCANCODE_DOWN])
		if (y + 0.75 * TANK_HEIGHT >= DISPLAY_HEIGHT)
			y = DISPLAY_HEIGHT - 0.75 * TANK_HEIGHT;
		else
		{
			angle = 180;
			turn = DOWN;
			y += TANK_SPEED;		
		}
	if (keyboardState[SDL_SCANCODE_SPACE] && sec > cooldown)
	{
		if (turn == LEFT)
			projectiles.push_back(new Projectile(renderer, x - 0.5 * TANK_WIDTH - 0.5 * PROJECTILE_HEIGHT, y + 0.5 * TANK_HEIGHT - 0.5 * PROJECTILE_HEIGHT, turn));
		else if (turn == RIGHT)
			projectiles.push_back(new Projectile(renderer, x + 1.5 * TANK_WIDTH + 0.25 * PROJECTILE_HEIGHT, y + 0.5 * TANK_HEIGHT - 0.5 * PROJECTILE_HEIGHT, turn));
		else if (turn == UP)
			projectiles.push_back(new Projectile(renderer, x + 0.5 * TANK_WIDTH - 0.5 * PROJECTILE_WIDTH, y - PROJECTILE_HEIGHT + 0.5 * PROJECTILE_WIDTH, turn));
		else
			projectiles.push_back(new Projectile(renderer, x + 0.5 * TANK_WIDTH - 0.5 * PROJECTILE_WIDTH, y + TANK_HEIGHT - 0.5 * PROJECTILE_WIDTH, turn));
		sec = 0;
	}
}

void Tank::Shote()
{
	for (size_t i = 0; i < projectiles.size(); ++i)
		projectiles[i]->Update();
}

void Tank::CleanProjectile()
{
	for (size_t i = 0; i < projectiles.size(); ++i)
		if (projectiles[i]->getX() <= 0 || projectiles[i]->getX() >= DISPLAY_WIDTH || projectiles[i]->getY() <= 0 || projectiles[i]->getY() >= DISPLAY_HEIGHT)
			projectiles.erase(projectiles.begin());
}