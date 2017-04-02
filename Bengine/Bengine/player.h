#pragma once
#include "game_object.h"

class Player
{

public:

	Player();
	explicit Player(BG::Sprite& sprite);
	~Player();

	void move(const BG::Vector2f& direction);

	BG::GameObject& game_object();

private:

	static const float kMovementSpeed;

	BG::GameObject* game_object_;
	BG::Sprite* sprite_;

};

