#pragma once
#include "game_object.h"

class Player
{

public:

	Player();

	explicit Player(BG::Sprite& sprite, const BG::Vector2f& position);
	~Player();

	void jump() const;

	void set_grounded(const bool& grounded);

	BG::GameObject& game_object() const;

private:

	static const float kJumpPower;

	bool grounded_;

	BG::GameObject* game_object_;
	BG::Sprite* sprite_;

};

