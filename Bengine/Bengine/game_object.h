#pragma once
#include "Vector2.h"
#include "transform.h"
#include "sprite.h"
#include <Dynamics/b2Body.h>
#include <Dynamics/b2Fixture.h>
#include <Collision/Shapes/b2PolygonShape.h>

namespace BG
{

	class GameObject
	{

	public:

		GameObject();
		GameObject(Sprite* sprite, const Vector2f &position);

		Transform& transform();

		void set_sprite(Sprite* sprite);
		Sprite& sprite() const;

		FloatRect bounds() const;

		void apply_physics(b2Body* body);

		void init_physics(b2BodyType body_type, float density);

		b2Body* rigidbody() const;

	protected:

		Transform transform_;
		Sprite* sprite_;
		b2Body* body_;

		void* foo;

	};

}

