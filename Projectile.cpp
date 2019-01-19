#include "Projectile.h"

using namespace std;

Projectile::Projectile(SDL_Renderer * renderer, double x, double y, Turn turn) : GameTexture(renderer, x, y) {
//	std::cout << "projectile constructor" << this << std::endl;
	SDL_Surface* surface = IMG_Load("images/projectile.png");
	projectileTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	height = PROJECTILE_HEIGHT;
	width = PROJECTILE_WIDTH;
	angle = 0;
	this->turn = turn;
}

Projectile::~Projectile() {
//	std::cout << "projectile destructor" << this << std::endl;
	SDL_DestroyTexture(projectileTexture);
}

void Projectile::Render() {
	SDL_Rect dstRect;

	dstRect.x = int(x);
	dstRect.y = int(y);
	dstRect.w = int(width);
	dstRect.h = int(height);

	if (turn == LEFT)
		angle = 270;
	else if (turn == UP)
		angle = 0;
	else if (turn == DOWN)
		angle = 180;
	else
		angle = 90;
//	SDL_RenderCopy(renderer, projectileTexture, NULL, &dstRect);
	SDL_RenderCopyEx(renderer, projectileTexture, 0, &dstRect, angle, NULL, SDL_FLIP_NONE);
}

void Projectile::Update() {
	Move();
}

void Projectile::Move() {
	if (turn == UP)
		y -= PROJECTILE_SPEED;
	else if (turn == DOWN)
		y += PROJECTILE_SPEED;
	else if (turn == LEFT)
		x -= PROJECTILE_SPEED;
	else
		x += PROJECTILE_SPEED;
}