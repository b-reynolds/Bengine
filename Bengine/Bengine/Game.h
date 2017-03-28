#pragma once
#include "window.h"
#include "sprite.h"
#include "game_object.h"
#include "Text.h"

#include "Box2D.h"
#include <vector>
#include <lauxlib.h>
#include <lstate.h>
#include "button.h"

#include "scn_main_menu.h"

class Game
{

public:

	Game();

	bool run(BG::Window* window);

	void exit();

private:

	BG::ScnMainMenu* scn_main_menu_;

	BG::Window* window_;

	bool initialized_;

	bool initialize();

	bool update();

	void draw();

};

