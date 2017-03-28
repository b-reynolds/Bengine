#include "scn_main_menu.h"
#include "resource_manager.h"
#include "window.h"
#include "bengine.h"

bool BG::ScnMainMenu::load()
{

	ResourceManager* resource_manager = ResourceManager::instance();

	// ----- Load Textures -----

	txtr_title_ = resource_manager->texture("Images/Main Menu/Title.png", window_);
	txtr_cloud_ = resource_manager->texture("Images/Main Menu/Cloud.png", window_);

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

	Vector2f btn_play_size = btn_play_->game_object().sprite().size();
	btn_play_->game_object().transform().set_origin(Vector2f(btn_play_size.x_ / 2.0f, btn_play_size.y_ / 2.0f));
	btn_play_->game_object().transform().set_position(Vector2f(window_->size().x_ / 2.0f, 368));

	btn_help_ = new Button(Vector2f(0, 0), txtr_btn_help_idle_, txtr_btn_help_hovered_, txtr_btn_help_clicked_, *window_);
	Vector2f btn_help_size = btn_help_->game_object().sprite().size();
	btn_help_->game_object().transform().set_origin(Vector2f(btn_help_size.x_ / 2.0f, btn_help_size.y_ / 2.0f));
	btn_help_->game_object().transform().set_position(Vector2f(window_->size().x_ / 2.0f, 502));

	btn_exit_ = new Button(Vector2f(0, 0), txtr_btn_exit_idle_, txtr_btn_exit_hovered_, txtr_btn_exit_clicked_, *window_);
	Vector2f btn_exit_size = btn_exit_->game_object().sprite().size();
	btn_exit_->game_object().transform().set_origin(Vector2f(btn_exit_size.x_ / 2.0f, btn_exit_size.y_ / 2.0f));
	btn_exit_->game_object().transform().set_position(Vector2f(window_->size().x_ / 2.0f, 625));

	buttons_.push_back(btn_play_);
	buttons_.push_back(btn_help_);
	buttons_.push_back(btn_exit_);

	// -------------------------

	// ----- Initialize Sprites -----

	spr_title_ = new Sprite(txtr_title_, window_);
	spr_cloud_ = new Sprite(txtr_cloud_, window_);

	// -------------------------

	// ----- Initialize Game Objects -----

	obj_title_ = new GameObject(spr_title_, Vector2f(0, 0));

	Vector2f obj_title_size = obj_title_->sprite().size();

	obj_title_->transform().set_origin(Vector2f(obj_title_size.x_ / 2.0f, obj_title_size.y_ / 2.0f));
	obj_title_->transform().set_position(window_->size().x_ / 2.0f, (obj_title_size.y_ / 2.0f) * 1.25f);

	obj_cloud_ = new GameObject(spr_cloud_, Vector2f(0.0f, -12.0f));
	obj_cloud_size = obj_cloud_->sprite().size();

	game_objects_.push_back(obj_cloud_);
	game_objects_.push_back(obj_title_);

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

	// ----- Update Cloud Animation -----

	obj_cloud_->transform().move(Vector2f(kCloudSpeed * Bengine::delta_time(), 0.0f));

	Vector2f obj_cloud_position = obj_cloud_->transform().position();

	if(obj_cloud_position.x_ >= window_->size().x_)
	{
		obj_cloud_->transform().set_position(Vector2f(-obj_cloud_size.x_, obj_cloud_position.y_));
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