#include "scn_game_over.h"
#include "resource_manager.h"
#include "Window.h"
#include "score_manager.h"

BG::ScnGameOver::ScnGameOver(Window& window, SceneManager& scene_manager) : Scene(window, scene_manager)
{
	sfx_button_click_ = nullptr;
	sfx_button_hover_ = nullptr;
	
	mus_loop_ = nullptr;

	fnt_score_ = nullptr;
	fnt_high_score_ = nullptr;

	txtr_background_ = nullptr;

	txtr_btn_back_idle_ = nullptr;
	txtr_btn_back_hovered_ = nullptr;
	txtr_btn_back_clicked_ = nullptr;

	txtr_btn_retry_idle_ = nullptr;
	txtr_btn_retry_hovered_ = nullptr;
	txtr_btn_retry_clicked_ = nullptr;

	btn_back_ = nullptr;
	btn_retry_ = nullptr;

	spr_background_ = nullptr;

	obj_background_ = nullptr;
}

bool BG::ScnGameOver::load()
{
	ResourceManager* resource_manager = ResourceManager::instance();

	// ----- Load Sound Effects -----

	sfx_button_click_ = resource_manager->sound_effect(kButtonClickPath);
	sfx_button_hover_ = resource_manager->sound_effect(kButtonHoverPath);

	// -------------------------

	// ----- Load Music -----

	mus_loop_ = resource_manager->music(kMusicLoopPath);

	// -------------------------

	// ----- Load Fonts -----

	fnt_score_ = resource_manager->font(kFontFilePath, kScoreFontSize);
	fnt_high_score_ = resource_manager->font(kFontFilePath, kHighScoreFontSize);

	// -------------------------

	// ----- Initialize Text -----

	ScoreManager* score_manager = ScoreManager::instance();

	Vector2f score_position = Vector2f(865.0f, 311.0f);
	txt_score_ = Text(fnt_score_, std::to_string(score_manager->score()), window_);
	txt_score_.set_colour(Colour(216, 0, 0, 255));
	FloatRect score_bounds = txt_score_.bounds();
	txt_score_.transform().set_position(Vector2f(score_position.x_ - (score_bounds.width_ / 2.0f), score_position.y_ - (score_bounds.height_ / 2.0f)));

	Vector2f high_score_position = Vector2f(911.0f, 496.0f);
	txt_high_score_ = Text(fnt_high_score_, std::to_string(score_manager->high_score()), window_);
	txt_high_score_.set_colour(Colour(216, 0, 0, 255));
	FloatRect high_score_bounds = txt_high_score_.bounds();
	txt_high_score_.transform().set_position(Vector2f(high_score_position.x_ - (high_score_bounds.width_ / 2.0f), high_score_position.y_ - (high_score_bounds.height_ / 2.0f)));

	// -------------------------

	// ----- Load Textures -----

	txtr_background_ = resource_manager->texture(kBackgroundFilePath, window_);

	txtr_btn_back_idle_ = resource_manager->texture(kBackButtonIdlePath, window_);
	txtr_btn_back_hovered_ = resource_manager->texture(kBackButtonHoveredPath, window_);
	txtr_btn_back_clicked_ = resource_manager->texture(kBackButtonClickedPath, window_);

	txtr_btn_retry_idle_ = resource_manager->texture(kRetryButtonIdlePath, window_);
	txtr_btn_retry_hovered_ = resource_manager->texture(kRetryButtonHoveredPath, window_);
	txtr_btn_retry_clicked_ = resource_manager->texture(kRetryButtonClickedPath, window_);

	// -------------------------

	// ----- Initialize Sprites -----

	spr_background_ = new Sprite(txtr_background_, window_);

	// -------------------------

	// ----- Initialize Game Objects -----

	obj_background_ = new GameObject(spr_background_, Vector2f(0.0f, 0.0f));

	// -------------------------

	// ----- Initialize Buttons -----

	btn_back_ = new Button(Vector2f(640.0f, 547.0f), txtr_btn_back_idle_, txtr_btn_back_hovered_, txtr_btn_back_clicked_, sfx_button_hover_, sfx_button_click_, *window_);
	buttons_.push_back(btn_back_);
	
	btn_retry_ = new Button(Vector2f(1011, 547), txtr_btn_retry_idle_, txtr_btn_retry_hovered_, txtr_btn_retry_clicked_, sfx_button_hover_, sfx_button_click_, *window_);
	buttons_.push_back(btn_retry_);

	// -------------------------

	// ----- Start Music -----

	Audio::stop_music(0);
	Audio::play_music(mus_loop_, -1, 0);
	Audio::set_music_volume(kMusicLoopVolume);

	// -------------------------

	loaded_ = true;

	return true;
}

bool BG::ScnGameOver::unload()
{
	ResourceManager* resource_manager = ResourceManager::instance();

	// ----- Free Sound Effects -----

	resource_manager->free_sound_effect(kButtonClickPath);
	resource_manager->free_sound_effect(kButtonHoverPath);

	// -------------------------

	// ----- Free Music -----

	resource_manager->free_music(kMusicLoopPath);

	// -------------------------

	// ----- Free Fonts -----

	resource_manager->free_font(kFontFilePath);
	resource_manager->free_font(kFontFilePath);

	// -------------------------

	// ----- Free Textures -----

	resource_manager->free_texture(kBackgroundFilePath);

	resource_manager->free_texture(kBackButtonIdlePath);
	resource_manager->free_texture(kBackButtonHoveredPath);
	resource_manager->free_texture(kBackButtonClickedPath);

	resource_manager->free_texture(kRetryButtonIdlePath);
	resource_manager->free_texture(kRetryButtonHoveredPath);
	resource_manager->free_texture(kRetryButtonClickedPath);

	// -------------------------

	// ----- Free Sprites -----

	delete spr_background_;

	// -------------------------

	// ----- Free Game Objects -----

	delete obj_background_;

	// -------------------------

	// ----- Free Buttons -----

	delete btn_back_;
	delete btn_retry_;

	buttons_.clear();

	// -------------------------

	loaded_ = false;

	return true;
}

bool BG::ScnGameOver::update()
{

	// ----- Update Buttons -----

	for (unsigned int i = 0; i < buttons_.size(); ++i)
		buttons_[i]->update();

	if (btn_retry_->clicked())
		return scene_manager_->transition_to("game");

	if (btn_back_->clicked())
		return scene_manager_->transition_to("main_menu");

	// -------------------------

	return true;
}

bool BG::ScnGameOver::draw()
{
	window_->clear();

	window_->draw(*obj_background_);

	window_->draw(txt_score_);
	window_->draw(txt_high_score_);

	for (unsigned int i = 0; i < buttons_.size(); ++i)
		window_->draw(*buttons_[i]);

	window_->display();

	return true;
}
