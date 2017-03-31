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

		/* Creates a Button */
		Button(const Vector2f& position, Texture* texture_idle, Texture* texture_hovered, Texture* texture_clicked, SoundEffect* sfx_hover, SoundEffect* sfx_click, Window& window);

		/* Returns a reference to the Button's underlying Game Object */
		GameObject& game_object();
		
		/* Update the button, checking if it is hovered/clicked and changing its state accordingly */
		void update();

		/* Returns true if the button is currently clicked */
		bool clicked() const;

	private:

		/* Holds a reference to the Mouse singleton */
		Mouse* mouse_;

		/* Button's idle sprite */
		Sprite* spr_idle_;

		/* Button's hovered sprite */
		Sprite* spr_hovered_;

		/* Button's clicked sprite */
		Sprite* spr_clicked_;

		/* Button's hover sound effect */
		SoundEffect* sfx_hover_;

		/* Button's clicked sound effect */
		SoundEffect* sfx_click_;

		/* Button's underlying Game Object*/
		GameObject game_object_;

		/* Button clicked state */
		bool clicked_;

		/* Button hovered state */
		bool hovered_;

	};
}
