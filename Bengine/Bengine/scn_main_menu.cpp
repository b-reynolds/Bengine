#include "scn_main_menu.h"
#include "resource_manager.h"
#include "window.h"
#include "bengine.h"
#include "World.h"
#include "random.h"
#include "Audio.h"

BG::ScnMainMenu::ScnMainMenu(Window& window, SceneManager& scene_manager) : Scene(window, scene_manager)
{
	txtr_background_ = nullptr;

	txtr_btn_play_idle_ = nullptr;
	txtr_btn_play_hovered_ = nullptr;
	txtr_btn_play_clicked_ = nullptr;

	txtr_btn_help_idle_ = nullptr;
	txtr_btn_help_hovered_ = nullptr;
	txtr_btn_help_clicked_ = nullptr;

	txtr_btn_exit_idle_ = nullptr;
	txtr_btn_exit_hovered_ = nullptr;
	txtr_btn_exit_clicked_ = nullptr;

	spr_background_ = nullptr;

	obj_background_ = nullptr;

	sfx_btn_click_ = nullptr;
	sfx_btn_hover = nullptr;

	mus_loop_ = nullptr;

	btn_play_ = nullptr;
	btn_help_ = nullptr;
	btn_exit_ = nullptr;
}

bool BG::ScnMainMenu::load()
{
	ResourceManager* resource_manager = ResourceManager::instance();

	// ----- Load Textures -----

	txtr_background_ = resource_manager->texture("Images/Main Menu/Background.png", window_);

	txtr_btn_play_idle_ = resource_manager->texture("Images/Main Menu/ButtonPlayIdle.png", window_);
	txtr_btn_play_hovered_ = resource_manager->texture("Images/Main Menu/ButtonPlayHovered.png", window_);
	txtr_btn_play_clicked_ = resource_manager->texture("Images/Main Menu/ButtonPlayClicked.png", window_);

	txtr_btn_help_idle_ = resource_manager->texture("Images/Main Menu/ButtonHelpIdle.png", window_);
	txtr_btn_help_hovered_ = resource_manager->texture("Images/Main Menu/ButtonHelpHovered.png", window_);
	txtr_btn_help_clicked_ = resource_manager->texture("Images/Main Menu/ButtonHelpClicked.png", window_);

	txtr_btn_exit_idle_ = resource_manager->texture("Images/Main Menu/ButtonExitIdle.png", window_);
	txtr_btn_exit_hovered_ = resource_manager->texture("Images/Main Menu/ButtonExitHovered.png", window_);
	txtr_btn_exit_clicked_ = resource_manager->texture("Images/Main Menu/ButtonExitClicked.png", window_);

	// -------------------------

	// ----- Load Sound Effects -----

	sfx_btn_hover = resource_manager->sound_effect("Audio/ButtonHover.wav");
	sfx_btn_click_ = resource_manager->sound_effect("Audio/ButtonClick.wav");

	// -------------------------

	// ----- Load Music -----

	mus_loop_ = resource_manager->music("Audio/MenuLoop.mp3");

	// -------------------------

	// ----- Initialize Buttons -----

	btn_play_ = new Button(Vector2f(0, 0), txtr_btn_play_idle_, txtr_btn_play_hovered_, txtr_btn_play_clicked_, sfx_btn_hover, sfx_btn_click_, *window_);
	btn_play_->game_object().transform().set_position(Vector2f(857, 576));
	buttons_.push_back(btn_play_);

	btn_help_ = new Button(Vector2f(0, 0), txtr_btn_help_idle_, txtr_btn_help_hovered_, txtr_btn_help_clicked_, sfx_btn_hover, sfx_btn_click_, *window_);
	btn_help_->game_object().transform().set_position(Vector2f(674, 584));
	buttons_.push_back(btn_help_);

	btn_exit_ = new Button(Vector2f(0, 0), txtr_btn_exit_idle_, txtr_btn_exit_hovered_, txtr_btn_exit_clicked_, sfx_btn_hover, sfx_btn_click_, *window_);
	btn_exit_->game_object().transform().set_position(Vector2f(1060, 576));
	buttons_.push_back(btn_exit_);

	// -------------------------

	// ----- Initialize Sprites -----

	spr_background_ = new Sprite(txtr_background_, window_);

	// -------------------------

	// ----- Initialize Game Objects -----

	obj_background_ = new GameObject(spr_background_, Vector2f(0.0f, 0.0f));
	game_objects_.push_back(obj_background_);

	// -------------------------

	// ----- Initialize Window -----

	window_->set_clear_colour(kBackgroundColour);

	// -------------------------

	// ----- Start Music -----

	Audio::play_music(mus_loop_, -1, 0);
	Audio::set_music_volume(128);

	// -------------------------

	loaded_ = true;

	return true;
}

bool BG::ScnMainMenu::unload()
{
	ResourceManager* resource_manager = ResourceManager::instance();

	// ----- Free Textures -----

	resource_manager->free_texture("Images/Main Menu/Background.png");

	resource_manager->free_texture("Images/Main Menu/ButtonPlayIdle.png");
	resource_manager->free_texture("Images/Main Menu/ButtonPlayHovered.png");
	resource_manager->free_texture("Images/Main Menu/ButtonPlayClicked.png");

	resource_manager->free_texture("Images/Main Menu/ButtonHelpIdle.png");
	resource_manager->free_texture("Images/Main Menu/ButtonHelpHovered.png");
	resource_manager->free_texture("Images/Main Menu/ButtonHelpClicked.png");

	resource_manager->free_texture("Images/Main Menu/ButtonExitIdle.png");
	resource_manager->free_texture("Images/Main Menu/ButtonExitHovered.png");
	resource_manager->free_texture("Images/Main Menu/ButtonExitClicked.png");

	// -------------------------

	// ----- Free Sound Effects -----

	resource_manager->free_sound_effect("Audio/ButtonHover.wav");
	resource_manager->free_sound_effect("Audio/ButtonClick.wav");

	// -------------------------

	// ----- Free Buttons -----

	delete btn_play_;
	delete btn_help_;
	delete btn_exit_;

	buttons_.clear();

	// -------------------------

	// ----- Free Music -----

	Audio::stop_music(0);
	resource_manager->free_music("Audio/MenuLoop.mp3");

	// -------------------------

	// ----- Free Sprites -----

	delete spr_background_;

	// -------------------------

	// ----- Free Game Objects -----

	delete obj_background_;

	game_objects_.clear();

	// -------------------------

	loaded_ = false;

	return true;
}

bool BG::ScnMainMenu::update()
{
	// ----- Update Buttons -----

	for (unsigned int i = 0; i < buttons_.size(); ++i)
	{
		buttons_[i]->update();
	}

	if(btn_play_->clicked())
	{
		return scene_manager_->transition_to("game");
	}

	if(btn_help_->clicked())
	{
		return scene_manager_->transition_to("help_screen");
	}

	if(btn_exit_->clicked())
	{
		unload();
		return false;
	}

	// -------------------------

	return true;
}

bool BG::ScnMainMenu::draw()
{
	window_->clear();

	// ----- Draw Game Objects -----

	for (unsigned int i = 0; i < game_objects_.size(); ++i)
	{
		window_->draw(*game_objects_[i]);
	}

	// -------------------------

	// ----- Draw Buttons -----

	for (unsigned int i = 0; i < buttons_.size(); ++i)
	{
		window_->draw(*buttons_[i]);
	}

	// -------------------------

	window_->display();

	return true;
}