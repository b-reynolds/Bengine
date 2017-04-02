#include "player.h"

const float Player::kMovementSpeed = 100.0f;

Player::Player()
{
	sprite_ = nullptr;
}

Player::Player(BG::Sprite& sprite)
{
	sprite_ = &sprite;

	game_object_ = new BG::GameObject(sprite_, BG::Vector2f(0, 0));

	game_object_->init_physics(b2_dynamicBody, 0.5f);

	game_object_->rigidbody()->SetFixedRotation(true);
}

Player::~Player()
{
	// Delete body
}

void Player::move(const BG::Vector2f& direction)
{
	game_object_->rigidbody()->ApplyForce(b2Vec2(direction.x_ * kMovementSpeed, direction.y_ * kMovementSpeed), b2Vec2_zero, true);
}

BG::GameObject& Player::game_object()
{
	return *game_object_;
}
