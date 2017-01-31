#pragma once
#include "Vector2D.h"

#define BUTTONS_MIN 1
#define BUTTONS_MAX 3

class Mouse
{

private:

	static Mouse *instance;
	Mouse();

	bool mouseState[BUTTONS_MAX] = { false };
	bool prevMouseState[BUTTONS_MAX] = { false };

	Vector2D<int> currentPosition;
	Vector2D<int> previousPosition;

public:

	static Mouse* getInstance();
	~Mouse();

	static Vector2D<int> getPosition();

	void setMouseState(const unsigned int &button, const bool &state);
	void swapStates();

	bool isButtonDown(const unsigned int &button);
	bool isButtonPressed(const unsigned int &button);
	bool isButtonReleased(const unsigned int &button);
	bool isButtonUp(const unsigned int &button);

};

