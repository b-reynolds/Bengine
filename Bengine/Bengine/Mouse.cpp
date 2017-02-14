#include "Mouse.h"
#include "Logger.h"
#include <SDL.h>

BG::Mouse* BG::Mouse::instance = nullptr;

BG::Mouse::Mouse() { }

/**
* Returns a pointer to a singleton instance of the Mouse class
*/
BG::Mouse* BG::Mouse::getInstance()
{
	if(instance == nullptr)
	{
		instance = new Mouse();
	}
	return instance;
}

BG::Mouse::~Mouse()
{
	printf("Mouse deconstructing..\n");
}

/**
 * Returns the x and y coordinates of the mouse
 */
BG::Vector2i BG::Mouse::getPosition()
{
	auto mousePosition = Vector2i(0, 0);
	SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
	return mousePosition;
}

/**
* Set the current state of the mouse
* @param button The mouse button to be set (1 = Left, 2 = Middle, 3 = Right)
* @param state The state of the button (True = Down, False = Up)
*/
void BG::Mouse::setMouseState(const unsigned int& button, const bool& state)
{
	if (button < BUTTONS_MIN || button > BUTTONS_MAX) return;
	mouseState[button] = state;
	Logger::getInstance()->log(Logger::DEBUG, std::string("Mouse Button (") +
		std::to_string(button) + ") State: " + (state ? "Down" : "Up"));
}

/**
* Copies the current mouse state values into the previous mouse state values in preperation for a new frame
*/
void BG::Mouse::swapStates()
{
	for (auto i = BUTTONS_MIN; i <= BUTTONS_MAX; ++i)
	{
		prevMouseState[i] = mouseState[i];
	}
	previousPosition = currentPosition;
	currentPosition = getPosition();
	if (currentPosition != previousPosition)
	{
		Logger::getInstance()->log(Logger::DEBUG, "Mouse Position: " + std::to_string(currentPosition.x) +
			", " + std::to_string(currentPosition.y));
	}
}

/**
* Returns true if the specified button is currently down
* @param button The mouse button to poll
*/
bool BG::Mouse::isButtonDown(const unsigned int& button)
{
	if (button < BUTTONS_MIN || button > BUTTONS_MAX) return false;
	return mouseState[button];
}

/**
* Returns true if the specified button is currently down and was up in the previous frame
* @param button The mouse button to poll
*/
bool BG::Mouse::isButtonPressed(const unsigned int& button)
{
	if (button < BUTTONS_MIN || button > BUTTONS_MAX) return false;
	return mouseState[button] && !prevMouseState[button];
}

/**
* Returns true if the specified button is currently up and was down in the previous frame
* @param button The mouse button to poll
*/
bool BG::Mouse::isButtonReleased(const unsigned int& button)
{
	if (button < BUTTONS_MIN || button > BUTTONS_MAX) return false;
	return !mouseState[button] && prevMouseState[button];
}

/**
* Returns true if the specified button is up
* @param button The mouse button to poll
*/
bool BG::Mouse::isButtonUp(const unsigned int& button)
{
	if (button < BUTTONS_MIN || button > BUTTONS_MAX) return false;
	return !mouseState[button];
}