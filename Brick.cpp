#include "Brick.h"

Brick::Brick(SDL_Renderer * renderer, double x, double y) : Texture(renderer, x, y) {
	std::cout << "brick constructor" << this << std::endl;
	SDL_Surface* surface = IMG_Load("images/brick.png");
	brickTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	height = BRICK_HEIGHT;
	width = BRICK_WIDTH;
}

Brick::~Brick() {
	std::cout << "brick destructor" << this << std::endl;
	SDL_DestroyTexture(brickTexture);
}

void Brick::Render() {
	SDL_Rect dstRect;

	dstRect.x = int(x);
	dstRect.y = int(y);
	dstRect.w = int(width);
	dstRect.h = int(height);

	SDL_RenderCopy(renderer, brickTexture, 0, &dstRect);
}

void Brick::Update() {

}