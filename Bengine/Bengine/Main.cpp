#include "SDL.h"
#include "Logger.h"
#include "Vector2D.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL_image.h>
#include <iostream>
#include "Keyboard.h"

const int WIN_WIDTH = 1024;
const int WIN_HEIGHT = 576;
const char* WIN_TITLE = "Bengine";

SDL_Texture *txtrBackground;
SDL_Texture *txtrLogo;

bool running = true;

void update(SDL_Event &event)
{

	// Swap the previous and current key states
	Keyboard* keyboard = Keyboard::getInstance();

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			running = false;
		}
		else if(event.type == SDL_KEYDOWN)
		{
			// A key was pressed, update the key Keyboard class
			keyboard->setKeyState(event.key.keysym.sym, true);
		}
		else if(event.type == SDL_KEYUP)
		{
			keyboard->setKeyState(event.key.keysym.sym, false);
		}

		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			printf("Key (%d / %c)\n", event.key.keysym.sym, static_cast<char>(event.key.keysym.sym));
			printf("Down: %s\n", keyboard->isKeyDown(event.key.keysym.sym) ? "True" : "False");
			printf("Up: %s\n", keyboard->isKeyUp(event.key.keysym.sym) ? "True" : "False");
			printf("Pressed: %s\n", keyboard->isKeyPressed(event.key.keysym.sym) ? "True" : "False");
			printf("Released: %s\n", keyboard->isKeyReleased(event.key.keysym.sym) ? "True" : "False");
		}
	}

	keyboard->swapStates();


}

void draw(SDL_Renderer *renderer)
{
	// Clear the renderer
	SDL_RenderClear(renderer);

	auto tileSize = Vector2D<int>();
	SDL_QueryTexture(txtrBackground, nullptr, nullptr, &tileSize.x, &tileSize.y);

	auto tiles = Vector2D<int>(WIN_WIDTH / tileSize.x, WIN_HEIGHT / tileSize.y);

	for (int x = 0; x < tiles.x; ++x)
	{
		for (int y = 0; y < tiles.y; ++y)
		{
			Renderer::renderTexture(txtrBackground, renderer, x * tileSize.x, y * tileSize.y);
		}
	}

	auto logoSize = Vector2D<int>();
	SDL_QueryTexture(txtrLogo, nullptr, nullptr, &logoSize.x, &logoSize.y);

	Renderer::renderTexture(txtrLogo, renderer, WIN_WIDTH / 2 - logoSize.x / 2, WIN_HEIGHT / 2 - logoSize.y / 2);

	// Update the screen
	SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{
	// Initialize the video subsystem
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		// Subsystem initialization failed, report error and exit.
		Logger::logSDLError("Failed to initialize video subsystem");
		SDL_Quit();
		return 1;
	}

	// Initialize SDL_Image
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		Logger::logSDLError("Failed to load SDL_Image");
		SDL_Quit();
		return 1;
	}

	// Create the window used for rendering
	SDL_Window *window = SDL_CreateWindow(WIN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_OPENGL);
								 
	if (window == nullptr)
	{
		// Window creation failed, report error, clean up and exit.
		Logger::logSDLError("Failed to create window");
		SDL_Quit();
		return 1;
	}

	// Create a renderer with hardware acceleration and vsync enabled
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(renderer == nullptr)
	{
		// Render creation failed, report error, clean up and exit.
		Logger::logSDLError("Failed to create renderer");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	ResourceManager* resourceManager = ResourceManager::getInstance();

	txtrBackground = resourceManager->loadTexture("Images/tile.bmp", renderer);
	txtrLogo = resourceManager->loadTexture("Images/Icon/bengine.fw.png", renderer);

	SDL_Event event;
	while(running)
	{
		update(event);
		draw(renderer);
	}

	// Clean up and exit

	SDL_DestroyTexture(txtrBackground);
	SDL_DestroyTexture(txtrLogo);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
