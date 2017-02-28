#pragma once
#include "Vector2.h"
#include "transform.h"
#include "sprite.h"
#include <Dynamics/b2Body.h>

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

		b2BodyDef* body_def_;
		b2Body* body_;
		Transform transform_;
		Sprite* sprite_;

	};

}

