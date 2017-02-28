#pragma once
#include "Vector2.h"

// The range of mouse buttons handled
#define BUTTONS_MIN 1
#define BUTTONS_MAX 3

namespace BG
{
	/*
	* \brief Mouse Manager Clas
	*/
	class Mouse
	{

	public:

		/* Returns a pointer to a singleton instance of the Mouse class */
		static Mouse* instance();

		/* Returns the currentcoordinate position of the mouse */
		Vector2i position() const;

		/* Set the current state of a mouse button */
		void set_mouse_state(const unsigned int &button, const bool &state);

		/* Returns true if the specified button is currently down */
		bool button_down(const unsigned int &button);

		/* Returns true if the specified button is currently down and it was up in the previous frame */
		bool button_pressed(const unsigned int &button);

		/* Returns true if the specified button is currently up and it was down in the previous frame */
		bool button_released(const unsigned int &button);

		/* Returns true if the specified button is up */
		bool button_up(const unsigned int &button);

		/* Copies the current mouse state array into the previous mouse state array */
		void swap_states();

	private:

		/* Contains the current state of the mouse */
		bool mouse_state_[BUTTONS_MAX] = { false };

		/* Contains state of the mouse in the previous frame */
		bool prev_mouse_state_[BUTTONS_MAX] = { false };

		/* Contains the current coordinate position of the mouse */
		Vector2i current_position_;

		/* Contains the coordinate position of the mouse in the previous frame */
		Vector2i previous_position_;

		/* The singleton class instance */
		static Mouse* instance_;

	};
}