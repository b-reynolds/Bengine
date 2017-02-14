#pragma once
#include <SDL.h>
#include "Keyboard.h"
#include "Mouse.h"
#include "GameObject.h"
#include "Window.h"
#include "Logger.h"
#include "Timer.h"

class Game
{

private:

	const int WIN_WIDTH = 1024;
	const int WIN_HEIGHT = 576;
	const char* WIN_TITLE = "Bengine";

	Uint64 NOW;
	Uint64 LAST;

	BG::Window* myWindow;
	SDL_Event event;

	BG::Mouse* mouse;
	BG::Keyboard* keyboard;
	BG::Logger* logger;

	BG::Sprite sprLogo;
	BG::Sprite sprBackground;
	BG::Sprite sprThing;
	BG::Sprite sprMouse;

	BG::GameObject objLogo;
	BG::GameObject objBackground;
	BG::GameObject objThing;
	BG::GameObject objMouse;

	BG::Timer myTimer = BG::Timer(1);

	bool initialize();

	bool update();
	void draw();

	void exit() const;

public:

	static float deltaTime;

	bool run();

	Game();
	~Game();

};

