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
		static Mouse* getInstance();

		/* Returns the currentcoordinate position of the mouse */
		Vector2i getPosition() const;

		/* Set the current state of a mouse button */
		void setMouseState(const unsigned int &button, const bool &state);

		/* Returns true if the specified button is currently down */
		bool isButtonDown(const unsigned int &button);

		/* Returns true if the specified button is currently down and it was up in the previous frame */
		bool isButtonPressed(const unsigned int &button);

		/* Returns true if the specified button is currently up and it was down in the previous frame */
		bool isButtonReleased(const unsigned int &button);

		/* Returns true if the specified button is up */
		bool isButtonUp(const unsigned int &button);

		/* Copies the current mouse state array into the previous mouse state array */
		void swapStates();

	private:

		/* Contains the current state of the mouse */
		bool mouseState[BUTTONS_MAX] = { false };

		/* Contains state of the mouse in the previous frame */
		bool prevMouseState[BUTTONS_MAX] = { false };

		/* Contains the current coordinate position of the mouse */
		Vector2i currentPosition;

		/* Contains the coordinate position of the mouse in the previous frame */
		Vector2i previousPosition;

		/* The singleton class instance */
		static Mouse* instance;

	};
}