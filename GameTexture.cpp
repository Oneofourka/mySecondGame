#include "GameTexture.h"

GameTexture::GameTexture(SDL_Renderer * renderer, double x, double y) : Texture(renderer, x, y) {
//	std::cout << "GameTexture constructor" << this << std::endl;
	turn = UP;
	angle = 0;
}

Turn GameTexture::GetTurn() {
	return turn;
}

void GameTexture::SetTurn(Turn turn) {
	this->turn = turn;
}

GameTexture::~GameTexture() {
//	std::cout << "GameTexture destructor" << this << std::endl;
}