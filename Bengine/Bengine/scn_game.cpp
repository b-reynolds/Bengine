#include "scn_game.h"
#include "resource_manager.h"
#include "keyboard.h"
#include "Window.h"
#include "World.h"
#include "bengine.h"
#include "random.h"

BG::ScnGame::ScnGame(Window& window, SceneManager& scene_manager) : Scene(window, scene_manager)
{
	txtr_player_ = nullptr;
	txtr_background_ = nullptr;

	spr_player_ = nullptr;
	spr_background_ = nullptr;

	obj_background_ = nullptr;

	end_platform_x_ = 0.0f;
	platform_speed_ = 0.0f;
}

bool BG::ScnGame::load()
{
	ResourceManager* resource_manager = ResourceManager::instance();

	// ----- Load Textures -----

	txtr_player_ = resource_manager->texture("Images/Game/Player.png", window_);
	txtr_background_ = resource_manager->texture("Images/Game/Background1.png", window_);
	txtr_background_2_ = resource_manager->texture("Images/Game/Background2.png", window_);

	// -------------------------

	// ----- Initialize Sprites -----

	spr_player_ = new Sprite(txtr_player_, window_);
	spr_background_ = new Sprite(txtr_background_, window_);
	spr_background_2_ = new Sprite(txtr_background_2_, window_);

	// -------------------------

	// ----- Initialize Game Objects -----

	obj_background_ = new GameObject(spr_background_, Vector2f(0.0f, 0.0f));
	obj_background_2_ = new GameObject(spr_background_2_, Vector2f(spr_background_->size().x_, 0.0f));

	// -------------------------

	// ----- Initialize Player ----- // TODO: Clean

	player_ = Player(*spr_player_, Vector2f(spr_player_->size().x_ * 5.0f, window_->size().y_ - Platform::kTileSize * (kPlatformRows + 2)));

	// -------------------------

	int tiles_left = (window_->size().x_ / Platform::kTileSize) * 2;

	int row = kPlatformRows;

	while(tiles_left >= 2)
	{
		int tiles = Random::random_int(2, tiles_left >= 5 ? 5 : tiles_left);
		tiles_left -= tiles;

		if(platforms_.empty())
		{	
			platforms_.push_back(new Platform(Vector2f(0.0f, window_->size().y_ - Platform::kTileSize * row), tiles, window_));
			continue;
		}

		FloatRect last = platforms_[platforms_.size() - 1]->bounds();

		platforms_.push_back(new Platform(Vector2f(last.left_ + last.width_ + Platform::kTileSize / 2.0f, window_->size().y_ - Platform::kTileSize * row), tiles, window_));

		if(row > 1)
		{
			row--;
		}
	}



	platform_speed_ = 1000.0f;


	window_->set_clear_colour(kBackgroundColour);

	loaded_ = true;

	end_platform_x_ = 0.0f;

	return true;
}

bool BG::ScnGame::unload()
{
	ResourceManager* resource_manager = ResourceManager::instance();

	// ----- Free Textures -----

	resource_manager->free_texture("Images/Game/Player.png");
	resource_manager->free_texture("Images/Game/Background1.png");
	resource_manager->free_texture("Images/Game/Background2.png");

	// -------------------------

	// ----- Free Physics Objects -----

	for(unsigned int i = 0; i < platforms_.size(); ++i)
	{
		delete platforms_[i];
	}
	platforms_.clear();

	// -------------------------

	// ----- Free Sprites -----

	delete spr_player_;
	delete spr_background_;
	delete spr_background_2_;

	// -------------------------

	// ----- Free Game Objects -----

	delete obj_background_;
	delete obj_background_2_;

	// -------------------------

	loaded_ = false;

	return true;
}

bool BG::ScnGame::update()
{
	Keyboard* keyboard = Keyboard::instance();


	FloatRect player_bounds = player_.game_object().bounds();
	player_bounds.width_ += 20;
	player_bounds.left_ -= 10;
	player_bounds.top_ += player_bounds.height_;
	player_bounds.height_ /= 4;

	const float kBackgroundScrollSpeed = 100.0f;

	Vector2f v = Vector2f(-kBackgroundScrollSpeed * Bengine::delta_time(), 0.0f);

	obj_background_->transform().move(v);
	obj_background_2_->transform().move(v);

	if(obj_background_->transform().position().x_ <= -obj_background_->bounds().width_)
	{
		obj_background_->transform().set_position(Vector2f(obj_background_2_->bounds().left_ + obj_background_2_->bounds().width_, 0.0f));
	}

	if (obj_background_2_->transform().position().x_ <= -obj_background_2_->bounds().width_)
	{
		obj_background_2_->transform().set_position(Vector2f(obj_background_->bounds().left_ + obj_background_->bounds().width_, 0.0f));
	}

	window_->draw(player_bounds, kClrPink);

	bool grounded = false;
	for(unsigned int i = 0; i < platforms_.size(); ++i)
	{
		for(auto & segment : platforms_[i]->segments())
		{
			segment->rigidbody()->SetLinearVelocity(b2Vec2(-platform_speed_ * Bengine::delta_time(), 0.0f));

			if(grounded)
			{
				continue;
			}

			grounded = segment->bounds().intersects(player_bounds);
		}
	}
	player_.set_grounded(grounded);

	if(keyboard->key_pressed(SDLK_w))
	{
		player_.jump();
	}

	if (player_.game_object().transform().position().y_ > window_->size().y_ || player_.game_object().transform().position().x_ < 0)
	{
		return scene_manager_->transition_to("game");
	}

	// ----- Update Physics -----

	update_platforms();


	World::instance()->Step(1 / 60.0f, 8, 3);

	update_platforms();

	for (auto body = World::instance()->GetBodyList(); body != nullptr; body = body->GetNext())
	{
		auto game_object = static_cast<GameObject*>(body->GetUserData());

		if (game_object != nullptr && game_object->active())
		{
			game_object->apply_physics(body);
		}
	}

	b2Vec2 velocity = player_.game_object().rigidbody()->GetLinearVelocity();
	player_.game_object().rigidbody()->SetLinearVelocity(b2Vec2(10.0f * BG::Bengine::delta_time(), velocity.y));



	// -------------------------

	return true;
}

bool BG::ScnGame::draw()
{
	window_->clear();

	window_->draw(*obj_background_);
	window_->draw(*obj_background_2_);

	window_->draw(player_.game_object());

	for(unsigned int i = 0; i < platforms_.size(); ++i)
	{
		for(auto & segment : platforms_[i]->segments())
		{
			window_->draw(*segment);
		}
	}


	
	window_->display();

	return true;
}

void BG::ScnGame::update_platforms()
{


	for(unsigned int i = 0; i < platforms_.size(); ++i)
	{
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

		furthest_x += Platform::kTileSize * Random::random_int(kSpaceMin, kSpaceMax);		

		int row = 0;

		if(furthest_row == kPlatformRows)
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