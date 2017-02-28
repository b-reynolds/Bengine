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
		void set_position(const Vector2f &position);

		/* Set the Transform's position */
		void set_position(const float &x, const float &y);

		/* Returns the Transform's current position */
		Vector2f position() const;

		/* Move the Transform by the specified velocity */
		void move(const Vector2f &velocity);

		/* Move the Transform by the specified velocity */
		void move(const float &x, const float &y);

		/* Set the Transform's rotation (degrees) */
		void set_rotation(const float &angle);

		/* Returns the Transform's current rotation */
		float rotation() const;

		/* Rotate the Transform by the specified angle (degrees) */
		void rotate(const float &angle);

	private:

		/* Current position of the Transform */
		Vector2f position_;

		/* Current rotation of the Transform in degrees */
		float rotation_;

	};

}