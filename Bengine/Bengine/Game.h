#pragma once
#include <SDL.h>
#include "Keyboard.h"
#include "Mouse.h"

class Game
{

private:

	const int WIN_WIDTH = 1024;
	const int WIN_HEIGHT = 576;
	const char* WIN_TITLE = "Bengine";

	SDL_Window *window;
	SDL_Event event;
	SDL_Renderer *renderer;

	BG::Mouse *mouse;
	BG::Keyboard *keyboard;

	SDL_Texture *txtrBackground;
	SDL_Texture *txtrLogo;

	bool initialize();

	bool update();
	void draw();

public:

	bool run();

	Game();
	~Game();

};

