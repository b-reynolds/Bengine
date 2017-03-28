#include "game.h"
#include "bengine.h"
#include "resource_manager.h"
#include "math.h"
#include "World.h"
#include "Box2D/Common/b2Draw.h"

#include "lua.hpp"
#include "Lua.h"

#include "lua_functions.cpp"

#include "button.h"

Game::Game()
{
	window_ = nullptr;
	initialized_ = false;
}

bool Game::run(BG::Window* window)
{
	this->window_ = window;

	// If the game fails to initialize then discontinue
	if(!initialized_ && !((initialized_ = initialize())))
	{
		return false;
	}

	if (!update())
	{
		exit();
		return false;
	}

	draw();

	return true;
}

bool Game::initialize()
{
	//BG::GameObject* obj_block = new BG::GameObject(new BG::Sprite(BG::ResourceManager::instance()->texture("Images/box.png", window_), window_), BG::Vector2f(0, 0));
	//obj_block->init_physics(b2_dynamicBody, 0.5f);
	//game_objects.push_back(obj_block);

	//BG::GameObject* obj_ablock = new BG::GameObject(new BG::Sprite(BG::ResourceManager::instance()->texture("Images/floor.png", window_), window_), BG::Vector2f(0.0f, 128.0f));
	//obj_ablock->init_physics(b2_staticBody, 0.0f);
	//game_objects.push_back(obj_ablock);

	//BG::ResourceManager* resource_manager = BG::ResourceManager::instance();

	//BG::Texture* txtr_button_idle = resource_manager->texture("Images/Buttons/ButtonIdle.png", window_);
	//BG::Texture* txtr_button_hovered = resource_manager->texture("Images/Buttons/ButtonHovered.png", window_);
	//BG::Texture* txtr_button_clicked = resource_manager->texture("Images/Buttons/ButtonClicked.png", window_);

	//button_ = new BG::Button(BG::Vector2f(25, 25), txtr_button_idle, txtr_button_hovered, txtr_button_clicked, *window_);

	//buttons_.push_back(button_);

	//BG::Lua::instance()->register_function("DoSomething", lua_GetLockpickLevel);

	//std::string* lua_script = BG::ResourceManager::instance()->script("Scripts/script.lua");

	//BG::Lua::instance()->load_script(*lua_script, nullptr);

	//int status = lua_pcall(BG::Lua::instance()->state(), 0, 1, 0);

	//int result = lua_toboolean(BG::Lua::instance()->state(), -1);

	//printf("The result is %s\n", result == 1 ? "true" : "false");

	//std::string* lua_script = BG::ResourceManager::instance()->script("Scripts/script.lua");

	//lua_State* lua_state;

	//lua_state = luaL_newstate();
	//luaL_openlibs(lua_state);

	//int status = luaL_loadstring(lua_state, lua_script->c_str());
	//if(status)
	//{
	//	printf("Error: %s\n", lua_tostring(lua_state, -1));
	//	return false;
	//}

	//status = lua_pcall(lua_state, 0, 1, 0);

	//int result = lua_toboolean(lua_state, -1);

	//printf("The result is %s\n", result == 1 ? "true" : "false");

	//lua_close(lua_state);

	scn_main_menu_ = new BG::ScnMainMenu(*window_);
	scn_main_menu_->load();

	return true;
}

bool Game::update()
{
	//BG::World::instance()->Step(1 / 60.0f, 8, 3);

	//auto mouse = BG::Mouse::instance();

	//if(mouse->button_pressed(3))
	//{
	//	//BG::GameObject* obj_block = new BG::GameObject(new BG::Sprite(BG::ResourceManager::instance()->texture("Images/box.png", window_), window_), BG::Vector2f(BG::Mouse::instance()->position().x_, BG::Mouse::instance()->position().y_));
	//	//obj_block->init_physics(b2_dynamicBody, 0.5f);
	//	//game_objects.push_back(obj_block);
	//}
	//else if(mouse->button_pressed(1))
	//{
	//	//BG::GameObject* obj_block = new BG::GameObject(new BG::Sprite(BG::ResourceManager::instance()->texture("Images/floor.png", window_), window_), BG::Vector2f(BG::Mouse::instance()->position().x_, BG::Mouse::instance()->position().y_));
	//	//obj_block->init_physics(b2_staticBody, 0.0f);
	//	//game_objects.push_back(obj_block);
	//}

	//auto keyboard = BG::Keyboard::instance();

	//if(keyboard->key_down(SDLK_d))
	//{
	//	game_objects[0]->rigidbody()->ApplyForce(b2Vec2(1.0f, 0.0f), b2Vec2_zero, true);
	//}
	//else if(keyboard->key_down(SDLK_a))
	//{
	//	game_objects[0]->rigidbody()->ApplyForce(b2Vec2(-1.0f, 0.0f), b2Vec2_zero, true);
	//}

	//button_->update();

	//if(button_->clicked())
	//{
	//	return false;
	//}

	//printf("Delta Time: %f\n", BG::Bengine::delta_time());

	scn_main_menu_->update();

	return true;
}

void Game::draw()
{
	//window_->clear();

	//for (auto body = BG::World::instance()->GetBodyList(); body != nullptr; body = body->GetNext())
	//{
	//	auto game_object = static_cast<BG::GameObject*>(body->GetUserData());

	//	if (game_object != nullptr)
	//	{
	//		game_object->apply_physics(body);
	//	}
	//}

	//for(unsigned int i = 0; i < game_objects.size(); ++i)
	//{
	//	window_->draw(*game_objects[i]);
	//}

	//for (unsigned int i = 0; i < buttons_.size(); ++i)
	//{
	//	window_->draw(*buttons_[i]);
	//}

	//window_->display();

	scn_main_menu_->draw();

}

void Game::exit()
{

}