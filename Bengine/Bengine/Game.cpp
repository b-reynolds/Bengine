#include "game.h"
#include "bengine.h"
#include "resource_manager.h"
#include "math.h"
#include "World.h"

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
	BG::Texture* txtrLogo = BG::ResourceManager::instance()->texture("Images/Icon/bengine.fw.png", window_);
	spr_logo_ = BG::Sprite(txtrLogo, window_);

	BG::Vector2f logoSize = spr_logo_.size();
	BG::Vector2i windowSize = window_->size();

	obj_logo = BG::GameObject(&spr_logo_, BG::Vector2f(windowSize.x_ / 2 - logoSize.x_ / 2,
		windowSize.y_ / 2 - logoSize.y_ / 2));

	txt_my_other_text_ = BG::Text(BG::ResourceManager::instance()->font("Fonts/Horta.ttf", 64), "Hey", window_);

	txt_my_text_ = BG::Text(BG::ResourceManager::instance()->font("Fonts/Horta.ttf", 32), "Hi", window_);


	txt_my_text_.set_colour(BG::kClrWhite);
	txt_my_text_.set_text("Hello World");
	txt_my_text_.transform().set_position(BG::Vector2f(250, 250));

	txt_my_other_text_.set_colour(BG::kClrWhite);
	txt_my_other_text_.transform().set_position(BG::Vector2f(450, 250));


	return true;
}

bool Game::update()
{
	//BG::World::instance()->Step(1 / 60.0f, 8, 3);

	obj_logo.sprite()->set_origin(obj_logo.sprite()->size() / 2);
	obj_logo.transform()->rotate(1);

	txt_my_text_.transform().rotate(1);

	auto mouse = BG::Mouse::instance();

	if(mouse->button_down(3))
	{

	}
	else if(mouse->button_down(1))
	{

	}

	BG::Vector2f logoPosition = obj_logo.transform()->position();
	auto keyboard = BG::Keyboard::instance();
	
	if(keyboard->key_down(SDLK_w))
	{
		logoPosition.y_ -= kSpeed * BG::Bengine::delta_time();
	}
	else if(keyboard->key_down(SDLK_s))
	{
		logoPosition.y_ += kSpeed * BG::Bengine::delta_time();
	}

	if(keyboard->key_down(SDLK_a))
	{
		logoPosition.x_ -= kSpeed * BG::Bengine::delta_time();
	}
	else if(keyboard->key_down(SDLK_d))
	{
		logoPosition.x_ += kSpeed * BG::Bengine::delta_time();
	}

	obj_logo.transform()->set_position(logoPosition);

	return true;
}

void Game::draw()
{
	// Clear the renderer
	window_->clear();

	window_->draw(obj_logo);

	window_->draw(txt_my_text_);
	window_->draw(txt_my_other_text_);

	window_->draw(txt_my_other_text_.bounds(), BG::kClrRed);
	window_->draw(txt_my_text_.bounds(), BG::kClrRed);
	window_->draw(obj_logo.bounds(), BG::kClrRed);

	b2Body* body = BG::World::instance()->GetBodyList();

	while(body != nullptr)
	{
		BG::GameObject* game_object = static_cast<BG::GameObject*>(body->GetUserData());

		if(game_object != nullptr)
		{
			window_->draw(*game_object);
		}

		body = body->GetNext();
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