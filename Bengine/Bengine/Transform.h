#pragma once
#include "Vector2.h"

namespace BG
{
	/*
	 * Transformation Class
	 */
	class Transform
	{

	public:

		/* Default Constructor */
		Transform();

		/* Initializes the Transform at the specified position */
		explicit Transform(const Vector2f &position);

		/* Set the Transform's position */
		void setPosition(const Vector2f &position);

		/* Returns the Transform's current position */
		Vector2f getPosition() const;

		/* Move the Transform by the specified velocity */
		void move(const Vector2f &velocity);

		/* Set the Transform's rotation (degrees) */
		void setRotation(const float &angle);

		/* Returns the Transform's current rotation */
		float getRotation() const;

		/* Rotate the Transform by the specified angle (degrees) */
		void rotate(const float &angle);

	private:

		/* Current position of the Transform */
		Vector2f position;

		/* Current rotation of the Transform in degrees */
		float rotation;

	};

}