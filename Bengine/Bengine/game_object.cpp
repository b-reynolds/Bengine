#include "game_object.h"
#include "World.h"
#include "math.h"
#include <Box2D.h>

BG::GameObject::GameObject()
{
	sprite_ = nullptr;
	transform_.set_position(Vector2f(0.0f, 0.0f));
	active_ = true;
	colour_ = Colour(255, 255, 255, 255);
	body_ = nullptr;
}

BG::GameObject::GameObject(Sprite* sprite, const Vector2f& position)
{
	sprite_ = sprite;
	transform_.set_position(position);
	active_ = true;
	colour_ = Colour(255, 255, 255, 255);
	body_ = nullptr;
}

BG::GameObject::~GameObject()
{
	//delete sprite_;
}

/**
 * \brief Returns a reference to the Game Object's underlying Transform
 */
BG::Transform& BG::GameObject::transform()
{
	return transform_;
}

void BG::GameObject::set_position(const Vector2f& position)
{
	transform_.set_position(position);

	if(body_ != nullptr)
	{
		body_->SetTransform(b2Vec2(transform_.position().x_ / 30.0f, transform_.position().y_ / 30.0f), transform_.rotation());
	}
}

BG::Vector2f BG::GameObject::position() const
{
	return transform_.position();
}

/**
 * \brief Set the Game Object's Sprite
 */
void BG::GameObject::set_sprite(Sprite* sprite)
{
	sprite_ = sprite;
}

/**
 * \brief Returns a reference to the Game Object's underlying Sprite
 */
BG::Sprite& BG::GameObject::sprite() const
{
	return *sprite_;
}

/**
 * \brief Returns the Game Object's bounding box
 */
BG::FloatRect BG::GameObject::bounds() const
{
	Vector2f position = transform_.position();
	Vector2f size = sprite_->size();
	return FloatRect(position.x_, position.y_, size.x_, size.y_);
}

/**
 * \brief Updates the Game Object's Transform using a Box2D rigidbody
 * \param body rigidbody
 */
void BG::GameObject::apply_physics(b2Body* body)
{
	transform_.set_position(Vector2f(30 * body->GetPosition().x, 30 * body->GetPosition().y));
	transform_.set_rotation(Math::radiansToDegrees(body->GetAngle()));
}

/**
 * \brief Initialize / add a rigidbody to the Game Object
 * \param body_type rigidbody type
 * \param density rigidbody density
 */
void BG::GameObject::init_physics(b2BodyType body_type, float density, const Vector2f& origin)
{
	auto sprite_size = sprite_->size();
	transform_.set_origin(origin);

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

/**
 * \brief Returns the current Active state of the Game Object
 */
bool BG::GameObject::active() const
{
	return active_;
}

/**
 * \brief Set the Active state of the Game Object
 * \param state new state
 */
void BG::GameObject::set_active(const bool& state)
{
	active_ = state;
}

/**
 * \brief Set the Game Object's tint colour
 * \param colour new colour
 */
void BG::GameObject::set_colour(const Colour& colour)
{
	colour_ = colour;
}

/**
 * \brief Returns the Game Object's tint colour
 */
BG::Colour BG::GameObject::colour() const
{
	return colour_;
}

/**
 * \brief Returns a pointer to the Game Object's rigidbody
 */
b2Body* BG::GameObject::rigidbody() const
{
	return body_;
}
