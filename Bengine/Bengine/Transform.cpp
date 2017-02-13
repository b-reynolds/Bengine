#include "Transform.h"

BG::Transform::Transform()
{
	rotation = 0.0f;
}

BG::Transform::Transform(const Vector2f& position)
{
	this->position = position;
	rotation = 0.0f;
}

void BG::Transform::setPosition(const Vector2f& position)
{
	this->position = position;
}

BG::Vector2f BG::Transform::getPosition() const
{
	return position;
}

void BG::Transform::move(const Vector2f& velocity)
{
	position += velocity;
}

void BG::Transform::setRotation(const float& angle)
{
	rotation = angle;
}

float BG::Transform::getRotation() const
{
	return rotation;
}

void BG::Transform::rotate(const float& angle)
{
	rotation += angle;
}