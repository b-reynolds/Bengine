#pragma once
#include "window.h"
#include "sprite.h"
#include "game_object.h"
#include "Text.h"

class Game
{

public:

	bool run(BG::Window* window);

	void exit();

private:

	const int kSpeed = 250;

	BG::Text txt_my_text_;
	BG::Text txt_my_other_text_;

	BG::Sprite spr_logo_;
	BG::GameObject obj_logo;

	BG::Window* window_;

	bool initialized_;

	bool initialize();

	bool update();

	void draw();

};

