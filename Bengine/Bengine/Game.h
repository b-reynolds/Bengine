#pragma once
#include "window.h"
#include "scn_main_menu.h"
#include "scene_manager.h"
#include "scn_help_screen.h"
#include "scn_game.h"

class Game
{

public:

	Game();

	bool run(BG::Window* window);

	void exit();

private:

	BG::SceneManager scene_manager_;

	BG::ScnMainMenu* scn_main_menu_;
	BG::ScnHelpScreen* scn_help_screen_;
	BG::ScnGame* scn_game_;

	BG::Window* window_;

	bool initialized_;

	bool initialize();

	bool update() const;

	void draw() const;

};

