#pragma once
#include "game_object.h"

namespace BG
{
	/*
	 * \brief Button class
	 */
	class Button
	{

	public:	

		Button(const Vector2f& position, Texture* texture_idle, Texture* texture_hovered, Texture* texture_clicked, Window& window);

		GameObject& game_object();
		
		void update();

		bool clicked() const;

	private:

		Sprite* spr_idle_;
		Sprite* spr_hovered_;
		Sprite* spr_clicked_;

		GameObject game_object_;

		Vector2f position_;
		Vector2f size_;
		bool clicked_;

		void calculate_size();

	};
}
