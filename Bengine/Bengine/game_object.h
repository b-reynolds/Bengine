#pragma once
#include "Vector2.h"
#include "transform.h"
#include "sprite.h"
#include <Dynamics/b2Body.h>

namespace BG
{

	/**
	 * \brief Game Object class
	 */
	class GameObject
	{

	public:

		/* Default constructor */
		GameObject();

		/* Constructor */
		GameObject(Sprite* sprite, const Vector2f &position);

		/* Returns a reference to the Game Object's underlying Transform */
		Transform& transform();

		/* Set the Game Object's Sprite */
		void set_sprite(Sprite* sprite);

		/* Returns a reference to the Game Object's underlying Sprite */
		Sprite& sprite() const;

		/* Returns the Game Object's bounding box */
		FloatRect bounds() const;

		/* Updates the Game Object's Transform using a Box2D rigidbody */
		void apply_physics(b2Body* body);

		/* Initialize / add a rigidbody to the Game Object */
		void init_physics(b2BodyType body_type, float density);

		/* Set the Active state of the Game Object */
		void set_active(const bool& state);

		/* Returns the current Active state of the Game Object */
		bool active() const;

		/* Set the Game Object's tint colour */
		void set_colour(const Colour& colour);

		/* Returns the Game Object's tint colour */
		Colour colour() const;

		/* Returns a pointer to the Game Object's rigidbody */
		b2Body* rigidbody() const;

	protected:

		/* Game Object's Transform*/
		Transform transform_;

		/* Game Object's Sprite */
		Sprite* sprite_;

		/* Game Object's Box2D Rigidbody */
		b2Body* body_;

		/* Game Object's tint colour */
		Colour colour_;

		/* Game Object's active state */
		bool active_;

	};

}

