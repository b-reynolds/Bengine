#include "game.h"
#include "bengine.h"
#include "resource_manager.h"
#include "math.h"
#include "World.h"
#include "Box2D/Common/b2Draw.h"

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
	// Clear the renderer
	window_->clear();

	//obj_logo.initializeBody();

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

	//b2World* world = BG::World::instance();

	//int t = 0;
	//for(b2Body* body_iterator = world->GetBodyList(); body_iterator != nullptr; body_iterator = body_iterator->GetNext())
	//{
	//	
	//	printf("BODY %d\n", ++t);
	//	auto game_object = static_cast<BG::GameObject*>(body_iterator->GetUserData());
	//	
	//	game_object->transform()->set_position(30 * body_iterator->GetPosition().x, 30 * body_iterator->GetPosition().y);

	//	auto sprite = game_object->sprite();

	//	auto origin_temp = sprite->origin();
	//	
	//	game_object->sprite()->set_origin(BG::Vector2f(sprite->size().x_ / 2, sprite->size().y_ / 2));
	//	game_object->transform()->set_rotation(BG::Math::radiansToDegrees(body_iterator->GetAngle()));

	//	window_->draw(*game_object);

	//	game_object->sprite()->set_origin(origin_temp); // ???
	//}

	window_->display();
}

void Game::exit()
{

}