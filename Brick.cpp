#include "Brick.h"

Brick::Brick(SDL_Renderer * renderer, double x, double y, BrickType type) : Texture(renderer, x, y) {
	this->type = type;
	if (type == FULL_BRICK) {
		surface = IMG_Load("images/brick.png");
		height = BRICK_HEIGHT;
		width = BRICK_WIDTH;
		std::cout << "brick_full constructor" << this << std::endl;
	}
	else if (type == UP_BRICK) {
		surface = IMG_Load("images/up_brick.png");
		height = BRICK_HEIGHT / 2;
		width = BRICK_WIDTH;
		std::cout << "brick_up constructor" << this << std::endl;
	}
	else if (type == LEFT_BRICK) {
		surface = IMG_Load("images/left_brick.png");
		height = BRICK_HEIGHT;
		width = BRICK_WIDTH / 2;
		std::cout << "brick_left constructor" << this << std::endl;
	}
	else if (type == RIGHT_BRICK){
		surface = IMG_Load("images/right_brick.png");
		height = BRICK_HEIGHT;
		width = BRICK_WIDTH / 2;
		this->x += BRICK_WIDTH / 2;
		std::cout << "brick_right constructor" << this << std::endl;
	}
	else if (type == DOWN_BRICK) {
		surface = IMG_Load("images/down_brick.png");
		height = BRICK_HEIGHT / 2;
		width = BRICK_WIDTH;
		this->y += BRICK_HEIGHT / 2;
		std::cout << "brick_down constructor" << this << std::endl;
	}
	brickTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);	
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

BrickType Brick::getBrickType() {
	return type;
}