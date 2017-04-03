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
	
}

bool BG::ScnGame::load()
{
	ResourceManager* resource_manager = ResourceManager::instance();

	// ----- Load Textures -----

	txtr_player_ = resource_manager->texture("Images/Player/Player.png", window_);

	// -------------------------

	// ----- Initialize Sprites -----

	spr_player_ = new Sprite(txtr_player_, window_);

	// -------------------------

	// ----- Initialize Player ----- // TODO: Clean

	player_ = Player(*spr_player_, Vector2f(256, window_->size().y_ - (Platform::kTileSize * 3.0f)));


	// -------------------------

	int tiles_left = (window_->size().x_ / Platform::kTileSize) * 2;

	while(tiles_left != 0)
	{
		int tiles = Random::random_int(1, tiles_left >= 5 ? 5 : tiles_left);
		tiles_left -= tiles;

		if(platforms_.empty())
		{	
			platforms_.push_back(new Platform(Vector2f(0.0f, window_->size().y_ - Platform::kTileSize), tiles, window_));
			continue;
		}

		FloatRect last = platforms_[platforms_.size() - 1]->bounds();

		platforms_.push_back(new Platform(Vector2f(last.left_ + last.width_, last.top_), tiles, window_));
	}



	platform_speed_ = 1000.0f;


	window_->set_clear_colour(kClrBlack);

	loaded_ = true;

	end_platform_x_ = 0.0f;

	return true;
}

bool BG::ScnGame::unload()
{
	ResourceManager* resource_manager = ResourceManager::instance();

	// ----- Free Textures -----

	resource_manager->free_texture("Images/Player/Player.png");

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


	// -------------------------

	return true;
}

bool BG::ScnGame::draw()
{
	window_->clear();

	window_->draw(player_.game_object());

	for(unsigned int i = 0; i < platforms_.size(); ++i)
	{
		for(auto & segment : platforms_[i]->segments())
		{
			window_->draw(*segment);
		}
		window_->draw(platforms_[i]->bounds(), kClrGreen);
	}

	FloatRect player_bounds = player_.game_object().bounds();
	player_bounds.width_ += 20;
	player_bounds.left_ -= 10;
	player_bounds.top_ += player_bounds.height_;
	player_bounds.height_ /= 4;
	window_->draw(player_bounds, kClrPink);

	
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

		for(unsigned int j = 0; j < platforms_.size(); ++j)
		{
			platform_bounds = platforms_[j]->bounds();

			float platform_x = platform_bounds.left_ + platform_bounds.width_;

			if (platform_x > furthest_x)
			{
				furthest_x = platform_x;
			}
		}

		if(Random::random_int(0, kSpaceChance) == 3)
			furthest_x += Platform::kTileSize * Random::random_int(kSpaceMin, kSpaceMax);
		
		int row = Random::random_int(1, kPlatformRows);

		platforms_[i]->set_position(Vector2f(furthest_x, window_->size().y_ - Platform::kTileSize * row));
	}

	//for(unsigned int i = 0; i < platforms_.size(); ++i)
	//{
	//	if(platforms_[i]->bounds().left_ + platforms_[i]->bounds().width_ > 0)
	//	{
	//		continue;
	//	}

	//	float furthest_x = 0.0f;
	//	for (unsigned int j = 0; j < platforms_.size(); ++j)
	//	{
	//		float platform_x = platforms_[j]->bounds().left_ + platforms_[j]->bounds().width_;

	//		if(platform_x > furthest_x)
	//		{
	//			furthest_x = platform_x;
	//		}
	//	}

	//	furthest_x += Platform::kTileSize * Random::random_int(0, 4);
	//	float platform_y = window_->size().y_ - (Random::random_int(0, 1) == 0 ? Platform::kTileSize : (Platform::kTileSize * 2.0f));

	//	platforms_[i]->set_position(Vector2f(furthest_x, platform_y));
	//}

}