#include "player.h"
#include "World.h"
#include "Bengine.h"
#include "resource_manager.h"

const std::string Player::kTexturePlayerIdlePath = "Images/Game/Player.png";
const std::string Player::kTexturePlayerJumpPath = "Images/Game/PlayerJump.png";

const float Player::kJumpPower = 2000.0f;

Player::Player(const BG::Vector2f& position, BG::Window* window)
{
	BG::ResourceManager* resource_manager = BG::ResourceManager::instance();

	spr_idle_ = new BG::Sprite(resource_manager->texture(kTexturePlayerIdlePath, window), window);
	spr_jump_ = new BG::Sprite(resource_manager->texture(kTexturePlayerJumpPath, window), window);

	game_object_ = new BG::GameObject(spr_idle_, BG::Vector2f(0, 0));
	game_object_->init_physics(b2_dynamicBody, 0.5f, BG::Vector2f(0.0f, 0.0f));
	game_object_->rigidbody()->SetFixedRotation(true);
	game_object_->set_position(position);

	grounded_ = false;
}

Player::~Player()
{
	BG::ResourceManager* resource_manager = BG::ResourceManager::instance();

	if(spr_idle_ != nullptr)
	{
		resource_manager->free_texture(kTexturePlayerIdlePath);
		delete spr_idle_;
	}

	if(spr_jump_ != nullptr)
	{
		resource_manager->free_texture(kTexturePlayerJumpPath);
		delete spr_jump_;
	}

	if(game_object().rigidbody() != nullptr)
	{
		BG::World::instance()->DestroyBody(game_object().rigidbody());
	}
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
	game_object_->set_sprite(grounded_ ? spr_idle_ : spr_jump_);
}

BG::GameObject& Player::game_object() const
{
	return *game_object_;
}
