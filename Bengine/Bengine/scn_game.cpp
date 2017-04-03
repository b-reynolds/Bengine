#include "scn_game.h"
#include "resource_manager.h"
#include "keyboard.h"
#include "Window.h"
#include "World.h"
#include "bengine.h"
#include "random.h"

BG::ScnGame::ScnGame(Window& window, SceneManager& scene_manager) : Scene(window, scene_manager)
{
	txtr_background_ = nullptr;
	txtr_background_2_ = nullptr;

	spr_background_ = nullptr;

	obj_background_ = nullptr;

	player_ = nullptr;

	keyboard_ = nullptr;

	end_platform_x_ = 0.0f;
	platform_speed_ = 0.0f;
}

bool BG::ScnGame::load()
{
	ResourceManager* resource_manager = ResourceManager::instance();

	// ----- Load Fonts -----

	fnt_score_ = resource_manager->font(kScoreFontFilePath, kScoreTextSize);

	// -------------------------

	// ----- Load Music -----

	mus_loop_ = resource_manager->music(kMusicLoopFilePath);

	// -------------------------

	// ----- Load Textures -----

	txtr_background_ = resource_manager->texture(kBackgroundSegOneFilePath, window_);
	txtr_background_2_ = resource_manager->texture(kBackgroundSegTwoFilePath, window_);

	// -------------------------

	// ----- Initialize Sprites -----

	spr_background_ = new Sprite(txtr_background_, window_);
	spr_background_2_ = new Sprite(txtr_background_2_, window_);

	// -------------------------

	// ----- Initialize Text -----

	txt_score_ = Text(fnt_score_, "000", window_);
	txt_score_.set_colour(kClrWhite);
	txt_score_.transform().set_position(Vector2f(window_->size().x_ - txt_score_.bounds().width_ - 32.0f, 32.0f));

	// -------------------------

	// ----- Initialize Game Objects -----

	obj_background_ = new GameObject(spr_background_, Vector2f(0.0f, 0.0f));
	obj_background_2_ = new GameObject(spr_background_2_, Vector2f(spr_background_->size().x_, 0.0f));

	// -------------------------

	// ----- Initialize Player ----- //

	player_ = new Player(Vector2f(0.0f, window_->size().y_ - Platform::kTileSize * (kPlatformRowsMax + 2)), window_);
	player_desired_x_ = (window_->size().x_ / 2.0f) - (player_->game_object().bounds().width_ * 2.0f);

	// -------------------------

	// ----- Initialize Platforms ----- //

	int tiles_left = (window_->size().x_ / Platform::kTileSize) * 2;

	int row = kPlatformRowsMax;

	while(tiles_left >= kPlatformTilesMin)
	{
		int tiles = Random::random_int(kPlatformTilesMin, tiles_left >= kPlatformTilesMax ? kPlatformTilesMax : tiles_left);
		tiles_left -= tiles;

		if(platforms_.empty())
		{	
			platforms_.push_back(new Platform(Vector2f(0.0f, window_->size().y_ - Platform::kTileSize * row), tiles, window_));
			continue;
		}

		FloatRect last = platforms_[platforms_.size() - 1]->bounds();

		platforms_.push_back(new Platform(Vector2f(last.left_ + last.width_ + Platform::kTileSize / 2.0f, window_->size().y_ - Platform::kTileSize * row), tiles, window_));

		if(row > 1)
			row--;
	}

	end_platform_x_ = 0.0f;

	// -------------------------

	// ----- Initialize Timers ----- //

	tmr_score_ = Timer(100);

	// -------------------------

	// ----- Initialize Variable Defaults ----- //

	keyboard_ = Keyboard::instance();
	platform_speed_ = kPlatformSpeedDefault;
	background_scroll_speed_ = kBackgroundScrollSpeedDefault;
	score_ = 0;

	// -------------------------

	// ----- Start Music ----- //

	Audio::stop_music(0);
	Audio::play_music(mus_loop_, -1, 0);
	Audio::set_music_volume(kMusicLoopVolume);

	// -------------------------

	loaded_ = true;

	return true;
}

bool BG::ScnGame::unload()
{
	ResourceManager* resource_manager = ResourceManager::instance();

	// ----- Free Fonts -----

	resource_manager->free_font(kScoreFontFilePath);

	// -------------------------

	// ----- Free Music -----

	resource_manager->free_music(kMusicLoopFilePath);

	// -------------------------

	// ----- Free Textures -----

	resource_manager->free_texture(kBackgroundSegOneFilePath);
	resource_manager->free_texture(kBackgroundSegTwoFilePath);

	// -------------------------

	// ----- Free Physics Objects -----

	for(unsigned int i = 0; i < platforms_.size(); ++i)
	{
		delete platforms_[i];
	}

	platforms_.clear();

	// -------------------------

	// ----- Free Sprites -----

	delete spr_background_;
	delete spr_background_2_;

	// -------------------------

	// ----- Free Game Objects -----

	delete obj_background_;
	delete obj_background_2_;

	delete player_;

	// -------------------------

	loaded_ = false;

	return true;
}

bool BG::ScnGame::update()
{
	if (keyboard_->key_pressed(SDLK_ESCAPE))
		return scene_manager_->transition_to("main_menu");

	// ----- Update Background -----

	update_background();

	// -------------------------

	// ----- Update Player -----

	update_player();

	if (player_->game_object().transform().position().y_ > window_->size().y_ || player_->game_object().transform().position().x_ < 0)
	{
		return scene_manager_->transition_to("game");
	}

	// -------------------------

	// ----- Update Platforms -----

	update_platforms();

	// -------------------------

	// ----- Update Score -----

	update_score();

	// -------------------------

	// ----- Update Physics Objects -----

	World::instance()->Step(1 / 60.0f, 8, 3);

	for (auto body = World::instance()->GetBodyList(); body != nullptr; body = body->GetNext())
	{
		auto game_object = static_cast<GameObject*>(body->GetUserData());

		if (game_object != nullptr && game_object->active())
		{
			game_object->apply_physics(body);
		}
	}

	// -------------------------

	return true;
}

bool BG::ScnGame::draw()
{
	window_->clear();

	window_->draw(*obj_background_);
	window_->draw(*obj_background_2_);

	for(unsigned int i = 0; i < platforms_.size(); ++i)
	{
		std::vector<GameObject*> segments = platforms_[i]->segments();
		for(unsigned int j = 0; j < segments.size(); ++j)
		{
			window_->draw(*segments[j]);
		}
	}

	window_->draw(player_->game_object());

	window_->draw(txt_score_);

	window_->display();

	return true;
}

void BG::ScnGame::update_background() const
{
	Vector2f velocity = Vector2f(-background_scroll_speed_ * Bengine::delta_time(), 0.0f);

	obj_background_->transform().move(velocity);
	obj_background_2_->transform().move(velocity);

	if (obj_background_->transform().position().x_ <= -obj_background_->bounds().width_)
		obj_background_->transform().set_position(Vector2f(obj_background_2_->bounds().left_ + obj_background_2_->bounds().width_, 0.0f));

	if (obj_background_2_->transform().position().x_ <= -obj_background_2_->bounds().width_)
		obj_background_2_->transform().set_position(Vector2f(obj_background_->bounds().left_ + obj_background_->bounds().width_, 0.0f));
}

void BG::ScnGame::update_platforms()
{
	for(unsigned int i = 0; i < platforms_.size(); ++i)
	{	
		std::vector<GameObject*> segments = platforms_[i]->segments();
		for (unsigned int j = 0; j < segments.size(); ++j)
			segments[j]->rigidbody()->SetLinearVelocity(b2Vec2(-platform_speed_ * Bengine::delta_time(), 0.0f));

		FloatRect platform_bounds = platforms_[i]->bounds();
		if (platform_bounds.left_ + platform_bounds.width_ > 0)
			continue;

		float furthest_x = 0.0f;
		int furthest_row = 0;

		for(unsigned int j = 0; j < platforms_.size(); ++j)
		{
			platform_bounds = platforms_[j]->bounds();

			float platform_x = platform_bounds.left_ + platform_bounds.width_;

			if (platform_x > furthest_x)
			{
				furthest_x = platform_x;
				furthest_row = (window_->size().y_ - platform_bounds.top_) / Platform::kTileSize;
			}
		}

		furthest_x += Platform::kTileSize * Random::random_int(kPlatformSpaceTilesMin, kPlatformSpaceTilesMax);		

		int row;

		if(furthest_row == kPlatformRowsMax)
		{
			row = furthest_row - 1;
		}
		else if(furthest_row == 1)
		{
			row = furthest_row + 1;
		}
		else
		{
			row = Random::random_int(0, 1) == 0 ? furthest_row + 1 : furthest_row - 1;
		}

		platforms_[i]->set_position(Vector2f(furthest_x, window_->size().y_ - Platform::kTileSize * row));
	}
}

void BG::ScnGame::update_score()
{
	if (!tmr_score_.expired())
		return;

	score_ += kScoreIncrement;
	platform_speed_ += kPlatformSpeedIncrement;
	background_scroll_speed_ += kBackgroundScrollSpeedIncrement;

	txt_score_.set_text(std::to_string(score_));
	txt_score_.transform().set_position(Vector2f(window_->size().x_ - txt_score_.bounds().width_ - 32.0f, 32.0f));

	tmr_score_.reset();
}

void BG::ScnGame::update_player()
{
	bool grounded = false;
	
	// Create a bounding box that represents the position of the Player's feet 
	FloatRect players_feet = player_->game_object().bounds();
	players_feet.top_ += players_feet.height_;
	players_feet.height_ = 10.0f;

	for(unsigned int i = 0; i < platforms_.size(); ++i)
	{
		std::vector<GameObject*> segments = platforms_[i]->segments();
		for(unsigned int j = 0; j < segments.size(); ++j)
		{
			if (!players_feet.intersects(segments[j]->bounds()))
				continue;

			// If the Player's feet intersects with any platform segment they are grounded
			grounded = true;
			break;
		}

		if (grounded)
			break;
	}

	player_->set_grounded(grounded);

	if (keyboard_->key_pressed(SDLK_w))
	{
		player_->jump();
	}

	float player_speed = abs(player_->game_object().position().x_ - player_desired_x_);
	b2Body* player_body = player_->game_object().rigidbody();
	player_body->SetLinearVelocity(b2Vec2(player_speed * Bengine::delta_time(), player_body->GetLinearVelocity().y));


}
