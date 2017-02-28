#pragma once
#include <SDL.h>

// The range of key codes handled
#define KEYCODES_MIN 0
#define KEYCODES_MAX 255

namespace BG
{
	/*
	 * \brief Keyboard Manager Class
	 */
	class Keyboard
	{

	public:

		/* Returns a pointer to the singleton instance of the Keyboard class */
		static Keyboard* instance();

		/* Set the current state of a key */
		void set_key_state(const SDL_Keycode &key, const bool &state);

		/* Returns true if the specified key is currently down */
		bool key_down(const SDL_Keycode &key);

		/* Returns true if the specified key is currently down and it was up in the previous frame */
		bool key_pressed(const SDL_Keycode &key);

		/* Returns true if the specified key is currently up and it was down in the previous frame */
		bool key_released(const SDL_Keycode &key);

		/* Returns true if the specified key is up */
		bool key_up(const SDL_Keycode &key);

		/* Copies the current key state array into the previous key state array */
		void swap_states();

	private:

		/* Contains the current state of the keyboard */
		bool key_states_[KEYCODES_MAX] = { false };

		/* Stores the state of the keyvoard in the previous frame */
		bool prev_key_states_[KEYCODES_MAX] = { false };

		/* The singleton class instance */
		static Keyboard* instance_;

	};
}