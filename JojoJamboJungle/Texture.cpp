#include "Texture.h"

Texture::Texture()
{
	//Initialize
	this->renderer = nullptr;
	this->textureWidth = 0;
	this->textureHeight = 0;
}

Texture::~Texture()
{
	this->free();
}

bool Texture::loadTextureFromFile(std::string pathToTexture)
{
	//First remove previous texture 
	this->free();

	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(pathToTexture.c_str());
	if (surface == nullptr)
	{
		return false; // TO DO: comments should be added, try&catch and error handling
	}
	else
	{
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

		//Create new texture
		texture = SDL_CreateTextureFromSurface(this->renderer, surface);
		if (texture == nullptr)
		{
			return false; // TO DO: comments should be added, try&catch and error handling
		}
		else
		{
			//Set dimensions
			this->textureWidth = surface->w;
			this->textureHeight = surface->h;
		}

		//Remove old
		SDL_FreeSurface(surface);
	}

	this->texture = texture;

	return  (this->texture != nullptr);
}

void Texture::free()
{
	if (this->texture != nullptr)
	{
		SDL_DestroyTexture(this->texture);
		this->texture = nullptr;
		this->textureWidth = 0;
		this->textureHeight = 0;
	}
}

void Texture::render(int x, int y, int width, int height)
{
	SDL_Rect renderRect = { x, y, width, height };
	SDL_RenderCopy(this->renderer, this->texture, nullptr, &renderRect);
}

int Texture::getTextureWidth()
{
	return this->textureWidth;
}

int Texture::getTextureHeight()
{
	return this->textureHeight;
}

void Texture::setRenderer(SDL_Renderer * renderer)
{
	this->renderer = renderer;
}
