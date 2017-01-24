#include "SDL.h"
#include <stdio.h>

int winHeight = 600;
int winWidth = 800;
const char* winTitle = "Bengine";

int main(int argc, char* argv[])
{

	// Initialize the video subsystem
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		// Subsystem initialization failed, report error and exit.
		printf("Error: Failed to initialize video subsystem: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	// Create the window used for rendering
	SDL_Window *window = SDL_CreateWindow(winTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight, SDL_WINDOW_OPENGL);
								 
	if (window == nullptr)
	{
		// Window creation failed, report error and exit.
		printf("Error: Failed to create window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	// GAME LOOP

	SDL_Delay(3000);

	// Clean up and exit

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
