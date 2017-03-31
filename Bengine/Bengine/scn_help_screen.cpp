#include "scn_help_screen.h"
#include "Window.h"

BG::ScnHelpScreen::ScnHelpScreen(Window& window, SceneManager& scene_manager) : Scene(window, scene_manager)
{
}

bool BG::ScnHelpScreen::load()
{
	window_->set_clear_colour(kColourBackground);

	loaded_ = true;

	return true;
}

bool BG::ScnHelpScreen::unload()
{
	return true;
}

bool BG::ScnHelpScreen::update()
{
	return true;
}

bool BG::ScnHelpScreen::draw()
{
	window_->clear();

	window_->display();

	return true;
}
