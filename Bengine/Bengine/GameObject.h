#pragma once
#include "Vector2.h"
#include "Transform.h"
#include "Sprite.h"

namespace BG
{

	class GameObject
	{

	public:

		GameObject();
		GameObject(Sprite* sprite, const Vector2f &position);

		Transform* getTransform();

		void setSprite(Sprite* sprite);
		Sprite* getSprite() const;

		FloatRect getBounds() const;

			
	protected:

		Transform transform;
		Sprite* sprite;

	};

}

