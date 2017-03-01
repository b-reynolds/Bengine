#pragma once
#include "window.h"
#include "sprite.h"
#include "game_object.h"
#include "Text.h"

#include "Box2D.h"
#include <vector>

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

	std::vector<BG::GameObject*> game_objects;

	BG::Window* window_;

	bool initialized_;

	bool initialize();

	bool update();

	void draw();

};

