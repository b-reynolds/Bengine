#include "mouse.h"
#include "Logger.h"
#include <SDL.h>
#include <string>

// Initialize static member
BG::Mouse* BG::Mouse::instance_ = nullptr;

/**
 * \brief Returns a pointer to a singleton instance of the Mouse class
*/
BG::Mouse* BG::Mouse::instance()
{
	if(instance_ == nullptr)
	{
		instance_ = new Mouse();
	}
	return instance_;
}

/**
 * \brief Returns the currentcoordinate position of the mouse
*/
BG::Vector2i BG::Mouse::position() const
{
	Vector2i mousePosition = Vector2i(0, 0);
	SDL_GetMouseState(&mousePosition.x_, &mousePosition.y_);
	return mousePosition;
}

/**
 * \brief Set the current state of a mouse button
 * \param button mouse button to be set (1 = Left, 2 = Middle, 3 = Right)
 * \param state state of the button (True = Down, False = Up)
*/
void BG::Mouse::set_mouse_state(const unsigned int& button, const bool& state)
{
	if (button < BUTTONS_MIN || button > BUTTONS_MAX) return;
	mouse_state_[button] = state;
	Logger::instance().log(Logger::kDebug, std::string("Mouse Button (") +
		std::to_string(button) + ") State: " + (state ? "Down" : "Up"));
}

/**
* \brief Returns true if the specified button is currently down
* \param button mouse button to poll
*/
bool BG::Mouse::button_down(const unsigned int& button)
{
	if (button < BUTTONS_MIN || button > BUTTONS_MAX) return false;
	return mouse_state_[button];
}

/**
* \brief Returns true if the specified button is currently down and it was up in the previous frame
* \param button mouse button to poll
*/
bool BG::Mouse::button_pressed(const unsigned int& button)
{
	if (button < BUTTONS_MIN || button > BUTTONS_MAX) return false;
	return mouse_state_[button] && !prev_mouse_state_[button];
}

/**
* \brief Returns true if the specified button is currently up and it was down in the previous frame
* \param button mouse button to poll
*/
bool BG::Mouse::button_released(const unsigned int& button)
{
	if (button < BUTTONS_MIN || button > BUTTONS_MAX) return false;
	return !mouse_state_[button] && prev_mouse_state_[button];
}

/**
* \brief Returns true if the specified button is up
* \param button mouse button to poll
*/
bool BG::Mouse::button_up(const unsigned int& button)
{
	if (button < BUTTONS_MIN || button > BUTTONS_MAX) return false;
	return !mouse_state_[button];
}

/**
 * \brief Copies the current mouse state array into the previous mouse state array
 * Allows for comparisons against the last frames mouse states.
*/
void BG::Mouse::swap_states()
{
	for (auto i = BUTTONS_MIN; i <= BUTTONS_MAX; ++i)
	{
		prev_mouse_state_[i] = mouse_state_[i];
	}
	previous_position_ = current_position_;
	current_position_ = position();
	if (current_position_ != previous_position_)
	{
		Logger::instance().log(Logger::kDebug, "Mouse Position: " + std::to_string(current_position_.x_) +
			", " + std::to_string(current_position_.y_));
	}
}