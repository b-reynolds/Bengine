#include "game.h"
#include "bengine.h"
#include "resource_manager.h"
#include "scn_help_screen.h"

Game::Game()
{
	window_ = nullptr;
	initialized_ = false;
}

bool Game::run(BG::Window* window)
{
	this->window_ = window;

	// If the game fails to initialize then discontinue
	if(!initialized_ && !((initialized_ = initialize())))
	{
		return false;
	}

	if (!update())
	{
		exit();
		return false;
	}

	if(scene_manager_.current_scene().loaded())
		draw();

	return true;
}

bool Game::initialize()
{
	scn_main_menu_ = new BG::ScnMainMenu(*window_, scene_manager_);
	scene_manager_.add_scene("main_menu", *scn_main_menu_);

	scn_help_screen_ = new BG::ScnHelpScreen(*window_, scene_manager_);
	scene_manager_.add_scene("help_screen", *scn_help_screen_);

	scene_manager_.set_current_scene("main_menu");

	return true;
}

bool Game::update() const
{
	return scene_manager_.current_scene().update();
}

void Game::draw() const
{
	scene_manager_.current_scene().draw();
}

void Game::exit()
{

}