#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "GameConst.h"
#include <iostream>

class Texture {
public:
	Texture(SDL_Renderer * renderer, double x, double y);
	virtual ~Texture();
	void setX(double x);
	void setY(double y);
	double getX();
	double getY();
	int getWidth();
	int getHeight();

protected:
	SDL_Texture * texture;
	SDL_Renderer * renderer;
	SDL_Surface* surface;
	SDL_Rect dstRect;
	double x, y;
	int width, height;
};