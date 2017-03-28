#pragma once
#include "game_object.h"
#include "mouse.h"

namespace BG
{
	/*
	 * \brief Button class
	 */
	class Button
	{

	public:	

		Button(const Vector2f& position, Texture* texture_idle, Texture* texture_hovered, Texture* texture_clicked, SoundEffect* sfx_hover, SoundEffect* sfx_click, Window& window);

		GameObject& game_object();
		
		void update();

		bool clicked() const;

	private:

		Mouse* mouse_;

		Sprite* spr_idle_;
		Sprite* spr_hovered_;
		Sprite* spr_clicked_;

		SoundEffect* sfx_hover_;
		SoundEffect* sfx_click_;

		GameObject game_object_;

		Vector2i mouse_pos_;
		Vector2f position_;
		Vector2f size_;

		bool clicked_;
		bool hovered_;

		void calculate_size();

	};
}
