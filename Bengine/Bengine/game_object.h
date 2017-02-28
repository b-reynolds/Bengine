#pragma once
#include "Vector2.h"
#include "transform.h"
#include "sprite.h"

namespace BG
{

	class GameObject
	{

	public:

		GameObject();
		GameObject(Sprite* sprite, const Vector2f &position);

		Transform* transform();

		void set_sprite(Sprite* sprite);
		Sprite* sprite() const;

		FloatRect bounds() const;

			
	protected:

		Transform transform_;
		Sprite* sprite_;

	};

}

