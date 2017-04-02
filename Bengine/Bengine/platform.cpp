#include "platform.h"
#include "resource_manager.h"
#include "World.h"
#include <lstate.h>

const std::string Platform::kTextureLocation = "Images/Platforms/Platform.png";

Platform::Platform(const BG::Vector2f& size, const BG::Vector2f& position, const BG::Colour& colour, BG::Window& window)
{
	BG::ResourceManager* resource_manager = BG::ResourceManager::instance();

	texture_ = resource_manager->texture(kTextureLocation, &window);

	sprite_ = new BG::Sprite(texture_, &window);
	sprite_->set_size(size);


	game_object_ = new BG::GameObject(sprite_, position);
	game_object_->set_colour(colour);

	game_object_->init_physics(b2_kinematicBody, 5.0f, BG::Vector2f(0.0f, 0.0f));

	game_object_->set_position(position);
}

Platform::~Platform()
{
	BG::ResourceManager* resource_manager = BG::ResourceManager::instance();
	
	resource_manager->free_texture(kTextureLocation);

	BG::World::instance()->DestroyBody(game_object_->rigidbody());

	delete sprite_;
}

BG::GameObject& Platform::game_object()
{
	return *game_object_;
}
