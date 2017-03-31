#include "scn_main_menu.h"
#include "resource_manager.h"
#include "window.h"
#include "bengine.h"
#include "World.h"
#include "random.h"
#include "Audio.h"

BG::ScnMainMenu::ScnMainMenu(Window& window, SceneManager& scene_manager) : Scene(window, scene_manager)
{
	txtr_title_ = nullptr;
	txtr_cloud_ = nullptr;
	txtr_box_ = nullptr;

	txtr_btn_play_idle_ = nullptr;
	txtr_btn_play_hovered_ = nullptr;
	txtr_btn_play_clicked_ = nullptr;

	txtr_btn_help_idle_ = nullptr;
	txtr_btn_help_hovered_ = nullptr;
	txtr_btn_help_clicked_ = nullptr;

	txtr_btn_exit_idle_ = nullptr;
	txtr_btn_exit_hovered_ = nullptr;
	txtr_btn_exit_clicked_ = nullptr;

	sfx_btn_click_ = nullptr;
	sfx_btn_hover = nullptr;

	mus_loop = nullptr;

	btn_play_ = nullptr;
	btn_help_ = nullptr;
	btn_exit_ = nullptr;

	spr_cloud_ = nullptr;
	spr_box_ = nullptr;
	spr_title_ = nullptr;

	obj_title_ = nullptr;
	obj_cloud_ = nullptr;
}

bool BG::ScnMainMenu::load()
{
	ResourceManager* resource_manager = ResourceManager::instance();

	// ----- Load Textures -----

	txtr_title_ = resource_manager->texture("Images/Main Menu/Title.png", window_);
	txtr_cloud_ = resource_manager->texture("Images/Main Menu/Cloud.png", window_);
	txtr_box_ = resource_manager->texture("Images/Main Menu/Box.png", window_);

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

	mus_loop = resource_manager->music("Audio/MenuLoop.wav");

	// -------------------------

	// ----- Initialize Buttons -----

	btn_play_ = new Button(Vector2f(0, 0), txtr_btn_play_idle_, txtr_btn_play_hovered_, txtr_btn_play_clicked_, sfx_btn_hover, sfx_btn_click_, *window_);
	btn_play_->game_object().transform().set_origin(btn_play_->game_object().sprite().size() / 2.0f);
	btn_play_->game_object().transform().set_position(Vector2f(window_->size().x_ / 2.0f, 368));
	buttons_.push_back(btn_play_);

	btn_help_ = new Button(Vector2f(0, 0), txtr_btn_help_idle_, txtr_btn_help_hovered_, txtr_btn_help_clicked_, sfx_btn_hover, sfx_btn_click_, *window_);
	btn_help_->game_object().transform().set_origin(btn_help_->game_object().sprite().size() / 2.0f);
	btn_help_->game_object().transform().set_position(Vector2f(window_->size().x_ / 2.0f, 502));
	buttons_.push_back(btn_help_);

	btn_exit_ = new Button(Vector2f(0, 0), txtr_btn_exit_idle_, txtr_btn_exit_hovered_, txtr_btn_exit_clicked_, sfx_btn_hover, sfx_btn_click_, *window_);
	btn_exit_->game_object().transform().set_origin(btn_exit_->game_object().sprite().size() / 2.0f);
	btn_exit_->game_object().transform().set_position(Vector2f(window_->size().x_ / 2.0f, 625));
	buttons_.push_back(btn_exit_);

	// -------------------------

	// ----- Initialize Sprites -----

	spr_title_ = new Sprite(txtr_title_, window_);
	spr_cloud_ = new Sprite(txtr_cloud_, window_);
	spr_box_ = new Sprite(txtr_box_, window_);

	// -------------------------

	// ----- Initialize Game Objects -----

	obj_cloud_ = new GameObject(spr_cloud_, Vector2f(spr_cloud_->size().x_ / 2.0f, 0.0f));
	obj_cloud_->transform().set_origin(spr_cloud_->size() / 2.0f);
	game_objects_.push_back(obj_cloud_);

	obj_title_ = new GameObject(spr_title_, Vector2f(0, 0));
	obj_title_->transform().set_origin(obj_title_->sprite().size() / 2.0f);
	obj_title_->transform().set_position(window_->size().x_ / 2.0f, obj_title_->sprite().size().y_ / 2.0f * 1.25f);
	game_objects_.push_back(obj_title_);

	// -------------------------

	// ----- Initialize Cloud Rain -----

	for(unsigned int i = 0; i < kCloudRainPoolSize; ++i)
	{
		GameObject* obj_box = new GameObject(spr_box_, Vector2f(-spr_cloud_->size().x_ / 2.0f, obj_cloud_->transform().position().y_));
		obj_box->init_physics(b2_dynamicBody, 0.5f);
		obj_box->set_active(false);
		cloud_rain_pool.push_back(obj_box);
	}

	// -------------------------

	// ----- Initialize Window -----

	window_->set_clear_colour(kColourBackground);

	// -------------------------

	// ----- Start Music -----

	Audio::play_music(mus_loop, -1, 0);
	Audio::set_music_volume(32);

	// -------------------------

	loaded_ = true;

	return true;
}

bool BG::ScnMainMenu::unload()
{
	ResourceManager* resource_manager = ResourceManager::instance();

	// ----- Free Textures -----

	resource_manager->free_texture("Images/Main Menu/Title.png");
	resource_manager->free_texture("Images/Main Menu/Cloud.png");
	resource_manager->free_texture("Images/Main Menu/Box.png");

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
	resource_manager->free_music("Audio/MenuLoop.wav");

	// -------------------------

	// ----- Free Sprites -----

	delete spr_title_;
	delete spr_cloud_;
	delete spr_box_;

	// -------------------------

	// ----- Free Game Objects -----

	delete obj_title_;
	delete obj_cloud_;

	game_objects_.clear();

	// -------------------------

	// ----- Free Physics Objects -----

	b2World* world = World::instance();
	for(unsigned int i = 0; i < cloud_rain_pool.size(); ++i)
	{
		world->DestroyBody(cloud_rain_pool[i]->rigidbody());
		delete cloud_rain_pool[i];\
	}

	cloud_rain_pool.clear();

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

	}

	if(btn_help_->clicked())
	{
		return scene_manager_->set_current_scene("help_screen");
	}

	if(btn_exit_->clicked())
	{
		return false;
	}

	// -------------------------

	// ----- Update Cloud Animation -----

	obj_cloud_->transform().move(Vector2f(kCloudSpeed * Bengine::delta_time(), 0.0f));

	if(obj_cloud_->transform().position().x_ >= window_->size().x_)
	{
		obj_cloud_->transform().set_position(Vector2f(-spr_cloud_->size().x_ / 2.0f, obj_cloud_->transform().position().y_));
	}

	// -------------------------

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

	for(unsigned int i = 0; i < cloud_rain_pool.size(); ++i)
	{
		if(cloud_rain_pool[i]->active())
		{
			if (cloud_rain_pool[i]->transform().position().y_ >= window_->size().y_)
			{
				cloud_rain_pool[i]->set_active(false);
			}
			continue;
		}

		b2Body* rigidbody = cloud_rain_pool[i]->rigidbody();

		rigidbody->SetLinearDamping(0.0f);
		rigidbody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

		rigidbody->SetTransform(World::world_to_sim(obj_cloud_->transform().position() + spr_cloud_->size() / 2.0f), 0.0f);
		rigidbody->ApplyForce(b2Vec2(Random::random_int(-kCloudSpeed, kCloudSpeed), kCloudSpeed), b2Vec2_zero, true);

		cloud_rain_pool[i]->set_colour(kCloudRainColours[Random::random_int(0, kCloudRainColours.size() - 1)]);
		cloud_rain_pool[i]->set_active(true);
	}

	// -------------------------

	return true;
}

bool BG::ScnMainMenu::draw()
{
	window_->clear();

	// ----- Draw Cloud Rain -----

	for (unsigned int i = 0; i < cloud_rain_pool.size(); ++i)
	{
		window_->draw(*cloud_rain_pool[i]);
	}

	// -------------------------

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