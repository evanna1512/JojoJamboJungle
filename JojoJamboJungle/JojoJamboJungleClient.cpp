#include <stdio.h>
#include <thread>
#include "JojoJamboJungleClient.h"
#include "JohnPlayer.h"
#include "utils.h"

UDPConnection udpConnection;
std::thread t;

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

void JojoJamboJungleClient::connect() {

	
	std::string IP;
	int32_t localPort = 0;
	int32_t remotePort = 0;

	std::cout
		<< "\n==========================================================================================================\n"
		<< "UDP connection - A simple test for UDP connections using SDL_Net!"
		<< "\n==========================================================================================================\n"
		<< "You'll be asked to enter the following :"
		<< "\n\tRemote IP   : The IP you want to connect to"
		<< "\n\tRemote Port : The port you want to connect to"
		<< "\n\tLocal port  : Uour port"
		<< "\nLocal port should be the same as remote port on the other instance of the application"
		<< "\n==========================================================================================================\n\n";

	//std::cout << "Enter remote IP ( 127.0.0.1  for local connections ) : ";
	//std::cin >> IP;
	//std::cout << "...and remote port : ";
	//std::cin >> remotePort;

	//std::cout << "Enter local port : ";
	//std::cin >> localPort;

	udpConnection.Init("127.0.0.1", 321321, 123123);

	uint8_t command = 0;

	while (!udpConnection.WasQuit())
	{
		std::cout
			<< "Your command : "
			<< "\n\t0 : Send a message"
			<< "\n\t1 : Quit"
			<< "\n\t2 : Check for data"
			<< std::endl;

		std::cin >> command;

		if (command == '0')
			udpConnection.Send("This is a test");
		else if (command == '1')
			udpConnection.Send("quit");
		else if (command == '2')
			udpConnection.CheckForData();
		else
			std::cout << "Illegal command\n";
	}

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

			//try to init connection in new thread
			t = std::thread(&JojoJamboJungleClient::connect, this);
			//std::thread t(&JojoJamboJungleClient::connect, this);
			t.detach();

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
	JohnPlayer john(50, 50);

	while (!quitGame)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				quitGame = true;
			}

			if (e.key.keysym.sym == SDLK_RIGHT) {

				int currentPosition = john.getPositionX();
				currentPosition += 5;
				john.setPositionX(currentPosition);

				udpConnection.Send("Position x: " + std::to_string(john.getPositionX()) \
					+ " position y: " + std::to_string(john.getPositionY()));
				//xPlayer += 5;
			}

			if (e.key.keysym.sym == SDLK_LEFT) {

				int currentPosition = john.getPositionX();
				currentPosition -= 5;
				john.setPositionX(currentPosition);


				udpConnection.Send("Position x: " + std::to_string(john.getPositionX()) \
					+ " position y: " + std::to_string(john.getPositionY()));
				//xPlayer -= 5;
			}
		}

		//Clear
		SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(this->renderer);

		//Render
		this->backgroundTexture->render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		this->baseTexture->render(0, SCREEN_HEIGHT - this->baseTexture->getTextureHeight(), SCREEN_WIDTH, this->baseTexture->getTextureHeight());
		this->playerTexture->render(50 + john.getPositionX(), 390, 2 * this->playerTexture->getTextureWidth(), 2 * this->playerTexture->getTextureHeight());

		//Update
		SDL_RenderPresent(this->renderer);

	}
}