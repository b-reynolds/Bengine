#include "game.h"
#include "bengine.h"
#include "resource_manager.h"
#include "math.h"
#include "World.h"
#include "Box2D/Common/b2Draw.h"

#include "lua.hpp"
#include "Lua.h"

#include "lua_functions.cpp"

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
	BG::GameObject* obj_block = new BG::GameObject(new BG::Sprite(BG::ResourceManager::instance()->texture("Images/box.png", window_), window_), BG::Vector2f(0, 0));
	obj_block->init_physics(b2_dynamicBody, 0.5f);
	game_objects.push_back(obj_block);

	BG::GameObject* obj_ablock = new BG::GameObject(new BG::Sprite(BG::ResourceManager::instance()->texture("Images/floor.png", window_), window_), BG::Vector2f(0.0f, 128.0f));
	obj_ablock->init_physics(b2_staticBody, 0.0f);
	game_objects.push_back(obj_ablock);

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

	getchar();

	return true;
}

bool Game::update()
{
	BG::World::instance()->Step(1 / 60.0f, 8, 3);

	auto mouse = BG::Mouse::instance();

	if(mouse->button_pressed(3))
	{
		BG::GameObject* obj_block = new BG::GameObject(new BG::Sprite(BG::ResourceManager::instance()->texture("Images/box.png", window_), window_), BG::Vector2f(BG::Mouse::instance()->position().x_, BG::Mouse::instance()->position().y_));
		obj_block->init_physics(b2_dynamicBody, 0.5f);
		game_objects.push_back(obj_block);
	}
	else if(mouse->button_pressed(1))
	{
		BG::GameObject* obj_block = new BG::GameObject(new BG::Sprite(BG::ResourceManager::instance()->texture("Images/floor.png", window_), window_), BG::Vector2f(BG::Mouse::instance()->position().x_, BG::Mouse::instance()->position().y_));
		obj_block->init_physics(b2_staticBody, 0.0f);
		game_objects.push_back(obj_block);
	}

	auto keyboard = BG::Keyboard::instance();

	if(keyboard->key_down(SDLK_d))
	{
		game_objects[0]->rigidbody()->ApplyForce(b2Vec2(1.0f, 0.0f), b2Vec2_zero, true);
	}
	else if(keyboard->key_down(SDLK_a))
	{
		game_objects[0]->rigidbody()->ApplyForce(b2Vec2(-1.0f, 0.0f), b2Vec2_zero, true);
	}

	return true;
}

void Game::draw()
{
	window_->clear();

	for (auto body = BG::World::instance()->GetBodyList(); body != nullptr; body = body->GetNext())
	{
		auto game_object = static_cast<BG::GameObject*>(body->GetUserData());

		if (game_object != nullptr)
		{
			game_object->apply_physics(body);
		}
	}

	for(auto & game_object : game_objects)
	{
		window_->draw(*game_object);
	}

	window_->display();
}

void Game::exit()
{

}