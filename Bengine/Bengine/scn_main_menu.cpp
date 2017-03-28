#include "scn_main_menu.h"
#include "resource_manager.h"
#include "window.h"

bool BG::ScnMainMenu::load()
{

	ResourceManager* resource_manager = ResourceManager::instance();

	// ----- Load Textures -----

	txtr_title_ = resource_manager->texture("Images/Main Menu/Title.png", window_);

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

	// ----- Initialize Buttons -----

	btn_play_ = new Button(Vector2f(0, 0), txtr_btn_play_idle_, txtr_btn_play_hovered_, txtr_btn_play_clicked_, *window_);
	btn_help_ = new Button(Vector2f(0, 0), txtr_btn_help_idle_, txtr_btn_help_hovered_, txtr_btn_help_clicked_, *window_);
	btn_exit_ = new Button(Vector2f(0, 0), txtr_btn_exit_idle_, txtr_btn_exit_hovered_, txtr_btn_exit_clicked_, *window_);

	buttons_.push_back(btn_play_);
	buttons_.push_back(btn_help_);
	buttons_.push_back(btn_exit_);

	// -------------------------

	// ----- Initialize Sprites -----

	spr_title_ = new Sprite(txtr_title_, window_);

	// -------------------------

	// ----- Initialize Game Objects -----

	obj_title_ = new GameObject(spr_title_, Vector2f(0, 0));

	// -------------------------

	// ----- Initialize Window -----

	window_->set_clear_colour(kColourBackground);

	// -------------------------

	return true;

}

bool BG::ScnMainMenu::unload()
{

	ResourceManager* resource_manager = ResourceManager::instance();

	// ----- Free Textures -----

	resource_manager->free_texture("Images/Main Menu/Title.png");
	delete txtr_title_;

	resource_manager->free_texture("Images/Main Menu/ButtonPlayIdle.png");
	delete txtr_btn_play_idle_;
	resource_manager->free_texture("Images/Main Menu/ButtonPlayHovered.png");
	delete txtr_btn_play_hovered_;
	resource_manager->free_texture("Images/Main Menu/ButtonPlayClicked.png");
	delete txtr_btn_play_clicked_;

	resource_manager->free_texture("Images/Main Menu/ButtonHelpIdle.png");
	delete txtr_btn_help_idle_;
	resource_manager->free_texture("Images/Main Menu/ButtonHelpHovered.png");
	delete txtr_btn_help_hovered_;
	resource_manager->free_texture("Images/Main Menu/ButtonHelpClicked.png");
	delete txtr_btn_help_clicked_;

	resource_manager->free_texture("Images/Main Menu/ButtonExitIdle.png");
	delete txtr_btn_exit_idle_;
	resource_manager->free_texture("Images/Main Menu/ButtonExitHovered.png");
	delete txtr_btn_exit_hovered_;
	resource_manager->free_texture("Images/Main Menu/ButtonExitClicked.png");
	delete txtr_btn_exit_clicked_;

	// -------------------------

	// ----- Free Sprites -----

	delete spr_title_;

	// -------------------------

	// ----- Free Game Objects -----

	delete obj_title_;

	// -------------------------

	return true;

}

bool BG::ScnMainMenu::update()
{

	// ----- Update Buttons -----

	for (unsigned int i = 0; i < buttons_.size(); ++i)
	{
		buttons_[i]->update();
	}

	// -------------------------

	return true;

}

bool BG::ScnMainMenu::draw()
{

	// ----- Draw Buttons -----

	for (unsigned int i = 0; i < buttons_.size(); ++i)
	{
		window_->draw(*buttons_[i]);
	}

	// -------------------------

	return true;

}