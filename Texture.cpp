#include "Texture.h"

Texture::Texture(SDL_Renderer * renderer, double x, double y) {
//	std::cout << "texture constructor" << this << std::endl;
	this->renderer = renderer;
	this->x = x;
	this->y = y;
}

Texture::~Texture() {
//	std::cout << "texture destructor" << this << std::endl;
}

void Texture::setX(double x) {
	this->x = x;
}

void Texture::setY(double y) {
	this->y = y;
}

void Texture::setWidth(int width) {
	this->width = width;
}

void Texture::setHeight(int height) {
	this->height = height;
}

double Texture::getX() {
	return x;
}

double Texture::getY() {
	return y;
}

int Texture::getWidth() {
	return width;
}

int Texture::getHeight() {
	return height;
}