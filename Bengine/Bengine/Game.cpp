#include "game.h"
#include "bengine.h"

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

	scn_game_ = new BG::ScnGame(*window_, scene_manager_);
	scene_manager_.add_scene("game", *scn_game_);

	scn_game_over = new BG::ScnGameOver(*window_, scene_manager_);
	scene_manager_.add_scene("game_over", *scn_game_over);

	scene_manager_.transition_to("main_menu");

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
	scene_manager_.current_scene().unload();
}