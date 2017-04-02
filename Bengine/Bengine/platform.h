#pragma once
#include "game_object.h"
#include <string>

class Platform
{

public:

	Platform(const BG::Vector2f& size, const BG::Vector2f& position, const BG::Colour& colour, BG::Window& window);
	~Platform();

	BG::GameObject& game_object();

private:

	const static std::string kTextureLocation;

	BG::GameObject* game_object_;

	BG::Texture* texture_;
	BG::Sprite* sprite_;

};

