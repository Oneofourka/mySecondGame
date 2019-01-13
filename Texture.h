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
	void setWidth(int i);
	void setHeight(int i);
	double getX();
	double getY();
	int getWidth();
	int getHeight();

protected:
	SDL_Renderer * renderer;
	double x, y;
	int width, height;
};