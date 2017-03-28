#include "World.h"

b2World* BG::World::instance_ = nullptr;

b2World* BG::World::instance()
{
	if(instance_ == nullptr)
	{
		b2Vec2 kDefaultGravity = b2Vec2(0.0f, 9.8f);
		instance_ = new b2World(kDefaultGravity);
	}
	return instance_;
}

void BG::World::set_gravity(const BG::Vector2f& gravity)
{
	gravity_.x = gravity.x_;
	gravity_.y = gravity.y_;

	instance_->SetGravity(gravity_);
}