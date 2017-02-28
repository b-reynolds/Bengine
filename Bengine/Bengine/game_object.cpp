#include "game_object.h"

BG::GameObject::GameObject()
{
	sprite_ = nullptr;
}

BG::GameObject::GameObject(Sprite* sprite, const Vector2f& position)
{
	this->sprite_ = sprite;
	transform_.set_position(position);
}

BG::Transform* BG::GameObject::transform()
{
	return &transform_;
}


void BG::GameObject::set_sprite(Sprite* sprite)
{
	this->sprite_ = sprite;
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
