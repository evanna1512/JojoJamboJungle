#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Connection.h"
#include "Texture.h"

class JojoJamboJungleClient {
private:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	SDL_Window* mainWindow = nullptr;
	SDL_Renderer* renderer = nullptr;
	Texture* playerTexture = nullptr;
	Texture* backgroundTexture = nullptr;
	Texture* baseTexture = nullptr;

public:
	JojoJamboJungleClient();
	~JojoJamboJungleClient();

	//Basic game methods
	bool initializeGame();
	bool loadGameResources();
	void closeGame();
	void processGame();
	void mainLoop();
	void connect();
};



