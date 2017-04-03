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

	player_ = Player(*spr_player_);

	// -------------------------

	int tiles_left = window_->size().x_ / Platform::kTileSize;

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

	// ----- Free Sprites -----

	delete spr_player_;

	// -------------------------

	loaded_ = false;

	return true;
}

bool BG::ScnGame::update()
{
	Keyboard* keyboard = Keyboard::instance();

	static bool grounded;

	FloatRect player_bounds = player_.game_object().bounds();
	player_bounds.width_ += 20;
	player_bounds.left_ -= 10;
	player_bounds.top_ += player_bounds.height_;
	player_bounds.height_ /= 4;


	window_->draw(player_bounds, kClrPink);

	for(unsigned int i = 0; i < platforms_.size(); ++i)
	{

		for(auto & segment : platforms_[i]->segments())
		{
			FloatRect segment_bounds = segment->bounds();
			segment_bounds.height_ = Platform::kTileSize * 0.2f;

			if(segment_bounds.intersects(player_bounds))
			{
				grounded = true;
			}

			segment->rigidbody()->SetLinearVelocity(b2Vec2(-platform_speed_ * Bengine::delta_time(), 0.0f));
		}
	}

	if(keyboard->key_down(SDLK_a))
	{
		player_.move(Vector2f(-1.0f, 0.0f));
	}
	else if(keyboard->key_down(SDLK_d))
	{
		player_.move(Vector2f(1.0f, 0.0f));
	}

	if(keyboard->key_pressed(SDLK_w) && grounded)
	{
		player_.game_object().rigidbody()->SetLinearVelocity(b2Vec2(player_.game_object().rigidbody()->GetLinearVelocity().x, -1000.0f * Bengine::delta_time()));
		grounded = false;
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
		if(platforms_[i]->bounds().left_ + platforms_[i]->bounds().width_ > 0)
		{
			continue;
		}

		float furthest_x = 0.0f;
		for (unsigned int j = 0; j < platforms_.size(); ++j)
		{
			float platform_x = platforms_[j]->bounds().left_ + platforms_[j]->bounds().width_;

			if(platform_x > furthest_x)
			{
				furthest_x = platform_x;
			}
		}

		furthest_x += Platform::kTileSize * Random::random_int(0, 4);
		float platform_y = window_->size().y_ - (Random::random_int(0, 1) == 0 ? Platform::kTileSize : (Platform::kTileSize * 2.0f));

		platforms_[i]->set_position(Vector2f(furthest_x, platform_y));
	}

}