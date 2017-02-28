#include "game.h"
#include "bengine.h"
#include "resource_manager.h"

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
	obj_logo.sprite()->set_origin(obj_logo.sprite()->size() / 2);
	obj_logo.transform()->rotate(1);

	txt_my_text_.transform().rotate(1);


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

	// Update the screen
	window_->display();
}

void Game::exit()
{

}