#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Texture{
private:
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	int textureWidth;
	int textureHeight;

public:
	Texture();
	~Texture();

	bool loadTextureFromFile(std::string path);
	void render(int x, int y, int width, int height);
	void free();

	int getTextureWidth();
	int getTextureHeight();

	void setRenderer(SDL_Renderer*);
};