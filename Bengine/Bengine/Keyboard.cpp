#include "Keyboard.h"
#include "Logger.h"
#include <string>

// Initialize static member
BG::Keyboard* BG::Keyboard::instance = nullptr;

/**
* \brief Returns a pointer to the singleton instance of the Keyboard class
*/
BG::Keyboard* BG::Keyboard::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Keyboard();
	}
	return instance;
}

/**
 * \brief Set the current state of a key
 * \param key keycode to set
 * \param state state of the key
 */
void BG::Keyboard::setKeyState(const SDL_Keycode &key, const bool &state)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return;
	keyStates[key] = state;
	if (prevKeyStates[key] != keyStates[key])
	{
		Logger::getInstance().log(Logger::DEBUG, std::string("Key (") +
			std::to_string(key) + "/" + static_cast<char>(key) + ") State: " + (state ? "Down" : "Up"));
	}
}

/**
* \brief Returns true if the specified key is currently down
* \param key keycode to poll
*/
bool BG::Keyboard::isKeyDown(const SDL_Keycode &key)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return false;
	return keyStates[key];
}

/**
* \brief Returns true if the specified key is currently down and it was up in the previous frame
* \param key The keycode to poll
*/
bool BG::Keyboard::isKeyPressed(const SDL_Keycode &key)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return false;
	return keyStates[key] && !prevKeyStates[key];
}

/**
* \brief Returns true if the specified key is currently up and it was down in the previous frame
* \param key keycode to poll
*/
bool BG::Keyboard::isKeyReleased(const SDL_Keycode &key)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return false;
	return prevKeyStates[key] && !keyStates[key];
}

/**
* \brief Returns true if the specified key is up
* \param key keycode to poll
*/
bool BG::Keyboard::isKeyUp(const SDL_Keycode &key)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return false;
	return !keyStates[key];
}

/**
 * \brief Copies the current key state array into the previous key state array
 * Allows for comparisons against the last frames key states.
*/
void BG::Keyboard::swapStates()
{
	for(auto i = KEYCODES_MIN; i <= KEYCODES_MAX; ++i)
	{
		prevKeyStates[i] = keyStates[i];
	}
}