#include "scn_main_menu.h"
#include "resource_manager.h"
#include "window.h"
#include "bengine.h"
#include "World.h"
#include "random.h"

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
	sfx_btn_click = resource_manager->sound_effect("Audio/ButtonClick.wav");

	// -------------------------

	// ----- Initialize Buttons -----

	btn_play_ = new Button(Vector2f(0, 0), txtr_btn_play_idle_, txtr_btn_play_hovered_, txtr_btn_play_clicked_, sfx_btn_hover, sfx_btn_click, *window_);

	Vector2f btn_play_size = btn_play_->game_object().sprite().size();
	btn_play_->game_object().transform().set_origin(Vector2f(btn_play_size.x_ / 2.0f, btn_play_size.y_ / 2.0f));
	btn_play_->game_object().transform().set_position(Vector2f(window_->size().x_ / 2.0f, 368));

	btn_help_ = new Button(Vector2f(0, 0), txtr_btn_help_idle_, txtr_btn_help_hovered_, txtr_btn_help_clicked_, sfx_btn_hover, sfx_btn_click, *window_);
	Vector2f btn_help_size = btn_help_->game_object().sprite().size();
	btn_help_->game_object().transform().set_origin(Vector2f(btn_help_size.x_ / 2.0f, btn_help_size.y_ / 2.0f));
	btn_help_->game_object().transform().set_position(Vector2f(window_->size().x_ / 2.0f, 502));

	btn_exit_ = new Button(Vector2f(0, 0), txtr_btn_exit_idle_, txtr_btn_exit_hovered_, txtr_btn_exit_clicked_, sfx_btn_hover, sfx_btn_click, *window_);
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
	spr_box_ = new Sprite(txtr_box_, window_);

	// -------------------------

	// ----- Initialize Game Objects -----

	obj_title_ = new GameObject(spr_title_, Vector2f(0, 0));

	Vector2f obj_title_size = obj_title_->sprite().size();

	obj_title_->transform().set_origin(Vector2f(obj_title_size.x_ / 2.0f, obj_title_size.y_ / 2.0f));
	obj_title_->transform().set_position(window_->size().x_ / 2.0f, (obj_title_size.y_ / 2.0f) * 1.25f);

	obj_cloud_ = new GameObject(spr_cloud_, Vector2f(0, -0.0f));
	obj_cloud_size_ = obj_cloud_->sprite().size();
	obj_cloud_->transform().set_origin(Vector2f(obj_cloud_size_.x_ / 2.0f, obj_cloud_size_.y_ / 2.0f));
	obj_cloud_->transform().set_position(Vector2f(window_->size().x_ / 2.0f, obj_cloud_size_.y_));
	obj_cloud_position_ = obj_cloud_->transform().position();

	game_objects_.push_back(obj_cloud_);
	game_objects_.push_back(obj_title_);

	// -------------------------

	// ----- Initialize Cloud Rain -----

	for(unsigned int i = 0; i < kCloudRainPoolSize; ++i)
	{
		GameObject* obj_box = new GameObject(spr_box_, Vector2f(0.0f, window_->size().y_));
		obj_box->init_physics(b2_dynamicBody, 0.5f);
		obj_box->set_active(false);
		cloud_rain_pool.push_back(obj_box);
	}

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

	// ----- Free Sprites -----

	delete spr_title_;

	// -------------------------

	// ----- Free Game Objects -----

	delete obj_title_;

	// -------------------------

	// ----- Free Physics Objects -----

	b2World* world = World::instance();
	for(unsigned int i = 0; i < cloud_rain_pool.size(); ++i)
	{
		world->DestroyBody(cloud_rain_pool[i]->rigidbody());
		delete cloud_rain_pool[i];\
	}

	// -------------------------

	getchar();

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
		unload();
	}

	if(btn_help_->clicked())
	{
		
	}

	if(btn_exit_->clicked())
	{
		
	}

	// -------------------------

	// ----- Update Cloud Animation -----

	obj_cloud_->transform().move(Vector2f(kCloudSpeed * Bengine::delta_time(), 0.0f));
	obj_cloud_position_ = obj_cloud_->transform().position();

	if(obj_cloud_position_.x_ >= window_->size().x_)
	{
		obj_cloud_->transform().set_position(Vector2f(-obj_cloud_size_.x_, obj_cloud_position_.y_));
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

	for (unsigned int i = 0; i < cloud_rain_pool.size(); ++i)
	{
		if (!cloud_rain_pool[i]->active())
		{
			b2Body* rigidbody = cloud_rain_pool[i]->rigidbody();

			rigidbody->SetTransform(b2Vec2((obj_cloud_position_.x_ + obj_cloud_size_.x_ / 2.0f) / 30.0f, (obj_cloud_position_.y_ + obj_cloud_size_.y_ / 2.0f) / 30.0f), 0);
			rigidbody->SetLinearDamping(0.0f);
			rigidbody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			rigidbody->ApplyForce(b2Vec2(Random::random_int(-kCloudSpeed, kCloudSpeed), kCloudSpeed), b2Vec2_zero, true);
			cloud_rain_pool[i]->set_colour(kCloudRainColours[Random::random_int(0, kCloudRainColours.size() - 1)]);

			cloud_rain_pool[i]->set_active(true);
		}
		else if (cloud_rain_pool[i]->transform().position().y_ >= window_->size().y_)
		{
			cloud_rain_pool[i]->set_active(false);
		}
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