#include <stdio.h>
#include "JojoJamboJungleClient.h"

JojoJamboJungleClient::JojoJamboJungleClient()
{
	this->playerTexture = new Texture;
	this->backgroundTexture = new Texture;
	this->baseTexture = new Texture;
}

JojoJamboJungleClient::~JojoJamboJungleClient()
{
}

bool JojoJamboJungleClient::initializeGame()
{
	//Initialize
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return false;
	}
	else
	{
		//Set texture filtering
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Linear texture filtering is not enabled in game!");
		}

		//Create window
		this->mainWindow = SDL_CreateWindow("JojoJamboJungle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (this->mainWindow == NULL)
		{
			return false;
		}
		else
		{
			//Create renderer
			this->renderer = SDL_CreateRenderer(this->mainWindow, -1, SDL_RENDERER_ACCELERATED);
			if (this->renderer == NULL)
			{
				return false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Enable png loading
				int imageFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imageFlags) & imageFlags))
					return false;
			}
		}
	}

	return true;
}

bool JojoJamboJungleClient::loadGameResources()
{

	//Load
	this->playerTexture->setRenderer(this->renderer);
	this->backgroundTexture->setRenderer(this->renderer);
	this->baseTexture->setRenderer(this->renderer);

	//This should be replaced into other method
	if (!this->playerTexture->loadTextureFromFile("IMG/john_hagging.png"))
	{
		return false;
	}

	if (!this->backgroundTexture->loadTextureFromFile("IMG/main_background.png"))
	{
		return false;
	}

	if (!this->baseTexture->loadTextureFromFile("IMG/base.png"))
	{
		return false;
	}

	return true;
}

void JojoJamboJungleClient::closeGame()
{
	//Free
	this->playerTexture->free();
	this->backgroundTexture->free();
	this->baseTexture->free();

	//Destroy	
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->mainWindow);
	this->mainWindow = nullptr;
	this->renderer = nullptr; //first: all textures should be destroyed

	//Quit
	IMG_Quit();
	SDL_Quit();
}

void JojoJamboJungleClient::processGame()
{
	//TO DO: This code should be replaced
	try
	{
		initializeGame();
		try
		{
			loadGameResources();
			
			try
			{
				mainLoop();
			}
			catch (const std::exception&)
			{
				printf("Problem with running game. \n");
			}

		}
		catch (const std::exception&)
		{
			printf("Problem with loading game resources. \n");
		}

	}
	catch (const std::exception&)
	{
		printf("Problem with game initialization. \n");
	}

	closeGame();
}

void JojoJamboJungleClient::mainLoop() {

	bool quitGame = false;
	SDL_Event e;

	while (!quitGame)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				quitGame = true;
			}

			if (e.key.keysym.sym == SDLK_RIGHT) {

				//xPlayer += 5;
			}

			if (e.key.keysym.sym == SDLK_LEFT) {

				//xPlayer -= 5;
			}
		}

		//Clear
		SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(this->renderer);

		//Render
		this->backgroundTexture->render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		this->baseTexture->render(0, SCREEN_HEIGHT - this->baseTexture->getTextureHeight(), SCREEN_WIDTH, this->baseTexture->getTextureHeight());
		this->playerTexture->render(50, 390, 2 * this->playerTexture->getTextureWidth(), 2 * this->playerTexture->getTextureHeight());

		//Update
		SDL_RenderPresent(this->renderer);
	}
}