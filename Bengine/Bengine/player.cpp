#include "player.h"
#include "World.h"
#include "Bengine.h"

const float Player::kJumpPower = 2000.0f;

Player::Player()
{
	game_object_ = nullptr;
	sprite_ = nullptr;
	grounded_ = false;
}

Player::Player(BG::Sprite& sprite, const BG::Vector2f& position)
{
	sprite_ = &sprite;

	game_object_ = new BG::GameObject(sprite_, BG::Vector2f(0, 0));
	game_object_->init_physics(b2_dynamicBody, 0.5f, BG::Vector2f(0.0f, 0.0f));
	game_object_->rigidbody()->SetFixedRotation(true);
	game_object_->set_position(position);

	grounded_ = false;
}

Player::~Player()
{
	//BG::World::instance()->DestroyBody(game_object().rigidbody());
}

void Player::jump() const
{
	if(!grounded_)
	{
		return;
	}

	b2Vec2 velocity = game_object().rigidbody()->GetLinearVelocity();
	game_object().rigidbody()->SetLinearVelocity(b2Vec2(velocity.x, -kJumpPower * BG::Bengine::delta_time()));
}

void Player::set_grounded(const bool& grounded)
{
	grounded_ = grounded;
}

BG::GameObject& Player::game_object() const
{
	return *game_object_;
}
