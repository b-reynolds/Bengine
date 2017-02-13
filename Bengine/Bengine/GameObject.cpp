#include "GameObject.h"

BG::GameObject::GameObject()
{
	sprite = nullptr;
}

BG::GameObject::GameObject(Sprite* sprite, const Vector2f& position)
{
	this->sprite = sprite;
	transform.setPosition(position);
}

BG::Transform* BG::GameObject::getTransform()
{
	return &transform;
}


void BG::GameObject::setSprite(Sprite* sprite)
{
	this->sprite = sprite;
}

BG::Sprite* BG::GameObject::getSprite() const
{
	return sprite;
}

BG::FloatRect BG::GameObject::getBounds() const
{
	Vector2f position = transform.getPosition();
	Vector2i size = sprite->getSize();
	return FloatRect(position.x, position.y, size.x, size.y);
}
