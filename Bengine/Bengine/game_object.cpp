#include "game_object.h"
#include "World.h"

#include "Box2D/Box2D.h"
#include "math.h"

BG::GameObject::GameObject()
{
	sprite_ = nullptr;
	transform_.set_position(69.0f, 69.0f);
}

BG::GameObject::GameObject(Sprite* sprite, const Vector2f& position)
{
	sprite_ = sprite;
	transform_.set_position(position);
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

void BG::GameObject::apply_physics(b2Body* body)
{
	transform_.set_position(30 * body->GetPosition().x, 30 * body->GetPosition().y);
	transform_.set_rotation(Math::radiansToDegrees(body->GetAngle()));
}

void BG::GameObject::init_physics(b2BodyType body_type, float density)
{
	auto sprite_size = sprite_->size();
	transform_.set_origin(Vector2f(sprite_size.x_ / 2.0f, sprite_size.y_ / 2.0f));

	b2BodyDef body_def;
	body_def.position = b2Vec2(transform_.position().x_ / 30.f, transform_.position().y_ / 30.0f);
	body_def.type = body_type;
	body_def.userData = this;

	body_ = World::instance()->CreateBody(&body_def);

	body_->SetUserData(this);


	b2PolygonShape shape;
	shape.SetAsBox(sprite_->size().x_ / 2.0f / 30.0f, sprite_->size().y_ / 2.0f / 30.0f);

	b2FixtureDef fixture_def;
	fixture_def.density = density;
	fixture_def.shape = &shape;

	body_->CreateFixture(&fixture_def);
}

b2Body* BG::GameObject::rigidbody() const
{
	return body_;
}
