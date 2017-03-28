#pragma once
#include <SDL_stdinc.h>
#include <SDL.h>
#include "mouse.h"
#include "keyboard.h"
#include "window.h"

namespace BG
{
	class Bengine
	{

	public:

		static float delta_time();

		Bengine();

		bool run();	

	private:
		
		const char* kWinTitle = "Bengine";
		const int kWinWidth = 1280;
		const int kWinHeight = 720;

		static float delta_time_;

		Mouse* mouse_;
		Keyboard* keyboard_;
		Window* window_;

		SDL_Event event_;
		Uint64 current_;
		Uint64 last_;

		bool initialize();

		void exit();

	};
}
