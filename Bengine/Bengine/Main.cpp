#include "SDL.h"
#include "Logger.h"
#include "Vector2D.h"
#include <stdio.h>
#include <string>
#include "Renderer.h"
#include "ResourceManager.h"

const int WIN_WIDTH = 1024;
const int WIN_HEIGHT = 576;
const char* WIN_TITLE = "Bengine";

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

	SDL_Texture *txtrBackground = resourceManager->loadTexture("Images/tile.bmp", renderer);
	SDL_Texture *txtrLogo = resourceManager->loadTexture("Images/Icon/bengine.bmp", renderer);

	// GAME LOOP

	for(int i = 0; i < 10; ++i)
	{
		// Clear the renderer
		SDL_RenderClear(renderer);

		auto tileSize = Vector2D<int>();
		SDL_QueryTexture(txtrBackground, nullptr, nullptr, &tileSize.x, &tileSize.y);

		auto tiles = Vector2D<int>(WIN_WIDTH / tileSize.x, WIN_HEIGHT / tileSize.y);

		for(int x = 0; x < tiles.x; ++x)
		{
			for(int y = 0; y < tiles.y; ++y)
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

	// Clean up and exit

	SDL_DestroyTexture(txtrBackground);
	SDL_DestroyTexture(txtrLogo);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
