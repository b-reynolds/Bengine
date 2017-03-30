#include "transform.h"

/*
 * \brief Default Constructor
 */
BG::Transform::Transform()
{
	rotation_ = 0.0f;
}

/*
 * \brief Initializes the Transform at the specified position
 * \param position position
 */
BG::Transform::Transform(const Vector2f& position)
{
	this->position_ = position;
	rotation_ = 0.0f;
}

/*
 * \brief Set the Transform's position
 * \param position position
 */
void BG::Transform::set_position(const Vector2f& position)
{
	if(position.x_ != position_.x_)
	{
		position_.x_ = position.x_ - origin_.x_;
	}

	if (position.y_ != position_.y_)
	{
		position_.y_ = position.y_ - origin_.y_;
	}
}

/*
* \brief Set the Transform's position
* \param x x position
* \param y y position
*/
void BG::Transform::set_position(const float& x, const float& y)
{
	if(position_.x_ != x)
	{
		position_.x_ = x - origin_.x_;
	}

	if (position_.y_ != y)
	{
		position_.y_ = y - origin_.y_;
	}
}

/*
 * \brief Returns the Transform's current position
 */
BG::Vector2f BG::Transform::position() const
{
	return position_;
}

/*
 * \brief Move the Transform by the specified velocity
 * \param velocity movement velocity
 */
void BG::Transform::move(const Vector2f& velocity)
{
	position_ += velocity;
}

/*
* \brief Move the Transform by the specified velocity
* \param x x velocity
* \param y y velocity
*/
void BG::Transform::move(const float& x, const float& y)
{
	position_.x_ += x;
	position_.y_ += y;
}

/*
 * \brief Set the Transform's rotation (degrees)
 * \param angle angle (degrees)
 */
void BG::Transform::set_rotation(const float& angle)
{
	rotation_ = angle;
}

/*
 * \brief Returns the Transform's current rotation
 */
float BG::Transform::rotation() const
{
	return rotation_;
}

/*
 * \brief Rotate the Transform by the specified angle (degrees)
 * \brief angle angle (degrees)
 */
void BG::Transform::rotate(const float& angle)
{
	rotation_ += angle;
}

void BG::Transform::set_origin(const Vector2f& origin)
{
	origin_ = origin;
}

BG::Vector2f BG::Transform::origin() const
{
	return origin_;
}
