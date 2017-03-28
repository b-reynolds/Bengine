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

class Game
{

public:

	Game();

	bool run(BG::Window* window);

	void exit();

private:

	const int kSpeed = 250;

	BG::Text txt_my_text_;
	BG::Text txt_my_other_text_;

	BG::Button* button_;

	std::vector<BG::GameObject*> game_objects;
	std::vector<BG::Button*> buttons_;

	BG::Window* window_;

	bool initialized_;

	bool initialize();

	bool update();

	void draw();

};

