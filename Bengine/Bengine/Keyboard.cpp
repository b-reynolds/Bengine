#include "keyboard.h"
#include "Logger.h"
#include <string>

// Initialize static member
BG::Keyboard* BG::Keyboard::instance_ = nullptr;

/**
* \brief Returns a pointer to the singleton instance of the Keyboard class
*/
BG::Keyboard* BG::Keyboard::instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new Keyboard();
	}
	return instance_;
}

/**
 * \brief Set the current state of a key
 * \param key keycode to set
 * \param state state of the key
 */
void BG::Keyboard::set_key_state(const SDL_Keycode &key, const bool &state)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return;
	key_states_[key] = state;
	if (prev_key_states_[key] != key_states_[key])
	{
		Logger::instance().log(Logger::kDebug, std::string("Key (") +
			std::to_string(key) + "/" + static_cast<char>(key) + ") State: " + (state ? "Down" : "Up"));
	}
}

/**
* \brief Returns true if the specified key is currently down
* \param key keycode to poll
*/
bool BG::Keyboard::key_down(const SDL_Keycode &key)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return false;
	return key_states_[key];
}

/**
* \brief Returns true if the specified key is currently down and it was up in the previous frame
* \param key The keycode to poll
*/
bool BG::Keyboard::key_pressed(const SDL_Keycode &key)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return false;
	return key_states_[key] && !prev_key_states_[key];
}

/**
* \brief Returns true if the specified key is currently up and it was down in the previous frame
* \param key keycode to poll
*/
bool BG::Keyboard::key_released(const SDL_Keycode &key)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return false;
	return prev_key_states_[key] && !key_states_[key];
}

/**
* \brief Returns true if the specified key is up
* \param key keycode to poll
*/
bool BG::Keyboard::key_up(const SDL_Keycode &key)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return false;
	return !key_states_[key];
}

/**
 * \brief Copies the current key state array into the previous key state array
 * Allows for comparisons against the last frames key states.
*/
void BG::Keyboard::swap_states()
{
	for(auto i = KEYCODES_MIN; i <= KEYCODES_MAX; ++i)
	{
		prev_key_states_[i] = key_states_[i];
	}
}