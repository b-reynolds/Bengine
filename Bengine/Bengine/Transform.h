#pragma once
#include "Vector2.h"

namespace BG
{

	class Transform
	{

	public:

		Transform();
		explicit Transform(const Vector2f &position);

		void setPosition(const Vector2f &position);
		Vector2f getPosition() const;

		void move(const Vector2f &velocity);

		void setRotation(const float &angle);
		float getRotation() const;

		void rotate(const float &angle);

	private:

		Vector2f position;
		float rotation;

	};

}