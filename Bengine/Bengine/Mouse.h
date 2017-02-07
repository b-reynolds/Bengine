#pragma once
#include "Vector2.h"

#define BUTTONS_MIN 1
#define BUTTONS_MAX 3

namespace BG
{
	class Mouse
	{

	private:

		static Mouse *instance;
		Mouse();

		bool mouseState[BUTTONS_MAX] = { false };
		bool prevMouseState[BUTTONS_MAX] = { false };

		Vector2i currentPosition;
		Vector2i previousPosition;

	public:

		static Mouse* getInstance();
		~Mouse();

		static Vector2i getPosition();

		void setMouseState(const unsigned int &button, const bool &state);
		void swapStates();

		bool isButtonDown(const unsigned int &button);
		bool isButtonPressed(const unsigned int &button);
		bool isButtonReleased(const unsigned int &button);
		bool isButtonUp(const unsigned int &button);

	};
}

