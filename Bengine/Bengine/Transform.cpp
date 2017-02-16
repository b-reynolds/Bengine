#include "Transform.h"

/*
 * \brief Default Constructor
 */
BG::Transform::Transform()
{
	rotation = 0.0f;
}

/*
 * \brief Initializes the Transform at the specified position
 * \param position position
 */
BG::Transform::Transform(const Vector2f& position)
{
	this->position = position;
	rotation = 0.0f;
}

/*
 * \brief Set the Transform's position
 * \param position position
 */
void BG::Transform::setPosition(const Vector2f& position)
{
	this->position = position;
}

/*
* \brief Set the Transform's position
* \param x x position
* \param y y position
*/
void BG::Transform::setPosition(const float& x, const float& y)
{
	position.x = x;
	position.y = y;
}

/*
 * \brief Returns the Transform's current position
 */
BG::Vector2f BG::Transform::getPosition() const
{
	return position;
}

/*
 * \brief Move the Transform by the specified velocity
 * \param velocity movement velocity
 */
void BG::Transform::move(const Vector2f& velocity)
{
	position += velocity;
}

/*
* \brief Move the Transform by the specified velocity
* \param x x velocity
* \param y y velocity
*/
void BG::Transform::move(const float& x, const float& y)
{
	position.x += x;
	position.y += y;
}

/*
 * \brief Set the Transform's rotation (degrees)
 * \param angle angle (degrees)
 */
void BG::Transform::setRotation(const float& angle)
{
	rotation = angle;
}

/*
 * \brief Returns the Transform's current rotation
 */
float BG::Transform::getRotation() const
{
	return rotation;
}

/*
 * \brief Rotate the Transform by the specified angle (degrees)
 * \brief angle angle (degrees)
 */
void BG::Transform::rotate(const float& angle)
{
	rotation += angle;
}