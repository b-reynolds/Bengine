#pragma once
#include <SDL.h>

// The range of key codes handled
#define KEYCODES_MIN 0
#define KEYCODES_MAX 255

namespace BG
{
	/*
	 * \brief Keyboard Manager
	 */
	class Keyboard
	{

	public:

		/* Returns a pointer to the singleton instance of the Keyboard class */
		static Keyboard* getInstance();

		/* Set the current state of a key */
		void setKeyState(const SDL_Keycode &key, const bool &state);

		/* Returns true if the specified key is currently down */
		bool isKeyDown(const SDL_Keycode &key);

		/* Returns true if the specified key is currently down and was up in the previous frame */
		bool isKeyPressed(const SDL_Keycode &key);

		/* Returns true if the specified key is currently up and was down in the previous frame */
		bool isKeyReleased(const SDL_Keycode &key);

		/* Returns true if the specified key is up */
		bool isKeyUp(const SDL_Keycode &key);

		/* Copies the current key state values into the previous key state values */
		void swapStates();

	private:

		/* Stores the current state of the keyboard */
		bool keyStates[KEYCODES_MAX] = { false };

		/* Stores the state of the keyvoard in the previous frame */
		bool prevKeyStates[KEYCODES_MAX] = { false };

		/* Static instance of the Keyboard class */
		static Keyboard* instance;

	};
}

