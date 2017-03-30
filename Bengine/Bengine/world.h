#pragma once
#include <Dynamics/b2World.h>
#include "Vector2.h"

namespace BG
{

	class World
	{

	public:

		static b2World* instance();

		void set_gravity(const BG::Vector2f& gravity);
		
		static b2Vec2 world_to_sim(const Vector2f& vector);

	private:

		static b2World* instance_;

		b2Vec2 gravity_;
	

	};

}