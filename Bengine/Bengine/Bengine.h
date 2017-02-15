#pragma once
#include <SDL_stdinc.h>
#include <SDL.h>
#include "Mouse.h"
#include "Keyboard.h"
#include "Window.h"

namespace BG
{
	class Bengine
	{

	public:

		static float deltaTime;

		Bengine();

		bool run();	

	private:
		
		const char* WIN_TITLE = "Bengine";
		const int WIN_WIDTH = 800;
		const int WIN_HEIGHT = 600;

		Mouse* mouse;
		Keyboard* keyboard;
		Window* window;

		SDL_Event event;
		Uint64 current;
		Uint64 last;

		bool initialize();

		void exit();

	};
}
