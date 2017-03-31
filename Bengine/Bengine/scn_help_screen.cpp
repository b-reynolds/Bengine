#include "scn_help_screen.h"
#include "Window.h"
#include "resource_manager.h"
#include "audio.h"

BG::ScnHelpScreen::ScnHelpScreen(Window& window, SceneManager& scene_manager) : Scene(window, scene_manager)
{
	txtr_title_ = nullptr;

	txtr_btn_back_idle_ = nullptr;
	txtr_btn_back_hovered_ = nullptr;
	txtr_btn_back_clicked_ = nullptr;

	sfx_btn_hover_ = nullptr;
	sfx_btn_click_ = nullptr;
		
	spr_title_ = nullptr;

	obj_title_ = nullptr;

	btn_back_ = nullptr;
}

bool BG::ScnHelpScreen::load()
{
	ResourceManager* resource_manager = ResourceManager::instance();

	// ----- Load Textures -----

	txtr_title_ = resource_manager->texture("Images/Help Screen/Title.png", window_);

	txtr_btn_back_idle_ = resource_manager->texture("Images/Help Screen/ButtonBackIdle.png", window_);
	txtr_btn_back_hovered_ = resource_manager->texture("Images/Help Screen/ButtonBackHovered.png", window_);
	txtr_btn_back_clicked_ = resource_manager->texture("Images/Help Screen/ButtonBackClicked.png", window_);

	// -------------------------

	// ----- Load Sound Effects -----

	sfx_btn_hover_ = resource_manager->sound_effect("Audio/ButtonHover.wav");
	sfx_btn_click_ = resource_manager->sound_effect("Audio/ButtonClick.wav");

	// -------------------------

	// ----- Load Music -----

	mus_loop = resource_manager->music("Audio/MenuLoop.wav");

	// -------------------------

	// ----- Initialize Sprites -----

	spr_title_ = new Sprite(txtr_title_, window_);

	// -------------------------

	// ----- Initialize Game Objects -----

	obj_title_ = new GameObject(spr_title_, Vector2f(11, 16));
	game_objects_.push_back(obj_title_);

	// -------------------------

	// ----- Initialize Buttons -----

	btn_back_ = new Button(Vector2f(897, 610), txtr_btn_back_idle_, txtr_btn_back_hovered_, txtr_btn_back_clicked_, sfx_btn_hover_, sfx_btn_click_, *window_);

	buttons_.push_back(btn_back_);

	// -------------------------

	// ----- Initialzize Window -----

	window_->set_clear_colour(kColourBackground);

	// -------------------------

	// ----- Start Music -----

	Audio::play_music(mus_loop, -1, 0);
	Audio::set_music_volume(32);

	// -------------------------

	loaded_ = true;

	return true;
}

bool BG::ScnHelpScreen::unload()
{
	ResourceManager* resource_manager = ResourceManager::instance();

	// ----- Free Textures -----

	resource_manager->free_texture("Images/Help Screen/Title.png");

	resource_manager->free_texture("Images/Help Screen/ButtonBackIdle.png");
	resource_manager->free_texture("Images/Help Screen/ButtonBackHovered.png");
	resource_manager->free_texture("Images/Help Screen/ButtonBackClicked.png");

	// -------------------------

	// ----- Free Sprites -----

	delete spr_title_;

	// -------------------------

	// ----- Free Game Objects -----

	delete obj_title_;

	game_objects_.clear();

	// -------------------------

	// ----- Free Sound Effects -----

	resource_manager->free_sound_effect("Audio/ButtonHover.wav");
	resource_manager->free_sound_effect("Audio/ButtonClick.wav");

	// -------------------------

	// ----- Free Music -----

	resource_manager->free_music("Audio/MenuLoop.wav");

	// -------------------------

	// ----- Free Buttons -----

	delete btn_back_;

	buttons_.clear();

	// -------------------------
	
	loaded_ = false;

	return true;
}

bool BG::ScnHelpScreen::update()
{
	// ----- Update Buttons -----

	for (unsigned int i = 0; i < buttons_.size(); ++i)
	{
		buttons_[i]->update();
	}

	if(btn_back_->clicked())
	{
		return scene_manager_->transition_to("main_menu");
	}

	// -------------------------

	return true;
}

bool BG::ScnHelpScreen::draw()
{
	window_->clear();

	// ----- Draw Buttons -----

	for(unsigned int i = 0; i < buttons_.size(); ++i)
	{
		window_->draw(*buttons_[i]);
	}

	// -------------------------

	// ----- Draw Game Objects -----

	for (unsigned int i = 0; i < game_objects_.size(); ++i)
	{
		window_->draw(*game_objects_[i]);
	}

	// -------------------------

	window_->display();

	return true;
}
