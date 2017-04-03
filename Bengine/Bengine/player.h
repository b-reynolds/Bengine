#pragma once
#include "game_object.h"
#include <string>

class Player
{

public:

	explicit Player(const BG::Vector2f& position, BG::Window* window);
	~Player();

	void jump() const;

	void set_grounded(const bool& grounded);

	BG::GameObject& game_object() const;

private:

	static const std::string kTexturePlayerIdlePath;
	static const std::string kTexturePlayerJumpPath;
	
	static const float kJumpPower;

	BG::GameObject* game_object_;

	BG::Sprite* spr_idle_;
	BG::Sprite* spr_jump_;

	bool grounded_;

};

