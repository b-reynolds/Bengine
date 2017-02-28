#include "game_object.h"
#include "World.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"

BG::GameObject::GameObject()
{
	sprite_ = nullptr;
	body_def_ = nullptr;
}

BG::GameObject::GameObject(Sprite* sprite, const Vector2f& position)
{
	sprite_ = sprite;
	transform_.set_position(position);
	body_def_ = nullptr;

	//body_def_ = new b2BodyDef();

	//body_def_->type = b2_dynamicBody;

	//body_def_->userData = this;
	//World::instance()->CreateBody(body_def_);

	//b2Body* body = World::instance()->CreateBody(body_def_);


	//b2PolygonShape shape;

	//shape.SetAsBox(sprite->size().x_ / 2 / 30.0f, sprite->size().y_ / 2 / 30.0f);
	//b2FixtureDef fixture_def;

	//fixture_def.density = 1.0f;
	//fixture_def.friction = 0.7f;
	//fixture_def.shape = &shape;
	//body->CreateFixture(&fixture_def);


}

BG::Transform* BG::GameObject::transform()
{
	return &transform_;
}


void BG::GameObject::set_sprite(Sprite* sprite)
{
	sprite_ = sprite;
}

BG::Sprite* BG::GameObject::sprite() const
{
	return sprite_;
}

BG::FloatRect BG::GameObject::bounds() const
{
	Vector2f position = transform_.position();
	Vector2f size = sprite_->size();
	return FloatRect(position.x_, position.y_, size.x_, size.y_);
}
