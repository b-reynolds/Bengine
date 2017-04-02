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

	int tile_size = 64;
	int tiles_x = window_->size().x_ / tile_size;

	for(unsigned int i = 1; i < tiles_x; ++i)
	{
		platforms_.push_back(new Platform(Vector2f(tile_size, tile_size), Vector2f(tile_size * i, window_->size().y_ - tile_size / 2.0f), kClrGreen, *window_));
	}

	platform_speed_ = 1000.0f;

	loaded_ = true;



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

	if(keyboard->key_down(SDLK_a))
	{
		player_.move(Vector2f(-1.0f, 0.0f));
	}
	else if(keyboard->key_down(SDLK_d))
	{
		player_.move(Vector2f(1.0f, 0.0f));
	}

	// ----- Update Physics -----

	World::instance()->Step(1 / 60.0f, 8, 3);

	for (auto body = World::instance()->GetBodyList(); body != nullptr; body = body->GetNext())
	{
		auto game_object = static_cast<GameObject*>(body->GetUserData());

		if (game_object != nullptr)
		{
			game_object->apply_physics(body);
		}
	}

	update_platforms();

	// -------------------------

	return true;
}

bool BG::ScnGame::draw()
{
	window_->clear();

	window_->draw(player_.game_object());

	for(unsigned int i = 0; i < platforms_.size(); ++i)
	{
		window_->draw(platforms_[i]->game_object());
	}
	
	window_->display();

	return true;
}

void BG::ScnGame::update_platforms()
{
	for(unsigned int i = 0; i < platforms_.size(); ++i)
	{
		platforms_[i]->game_object().rigidbody()->SetLinearVelocity(b2Vec2(-platform_speed_ * Bengine::delta_time(), 0.0f));

		if(platforms_[i]->game_object().transform().position().x_ > -kPlatformTileSize)
		{
			continue;
		}

		Platform* end_platform = nullptr;
		for(unsigned int j = 0; j < platforms_.size(); ++j)
		{
			if(end_platform == nullptr)
			{
				end_platform = platforms_[j];
				continue;
			}

			if(platforms_[j]->game_object().transform().position().x_ > end_platform->game_object().transform().position().x_)
			{
				end_platform = platforms_[j];
			}
		}

		platforms_[i]->game_object().transform().set_position(Vector2f(end_platform->game_object().transform().position().x_ + (kPlatformTileSize * 2.0f), end_platform->game_object().transform().position().y_ + kPlatformTileSize));
		platforms_[i]->game_object().apply_world(platforms_[i]->game_object().rigidbody());
	}



}
