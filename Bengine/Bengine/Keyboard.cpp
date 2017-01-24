#include "Keyboard.h"
#include <cstdio>

Keyboard* Keyboard::instance = nullptr;

Keyboard::Keyboard() { }

/**
* Returns a reference to the singleton instance of the Keyboard class
*/
Keyboard* Keyboard::getInstance()
{
	if(instance == nullptr)
	{
		instance = new Keyboard();
	}
	return instance;
}

Keyboard::~Keyboard()
{
	delete instance;
}

/**
* Set the current state of a key
* @param key The keycode to set
* @param state The state of the key (True = Down, False = Up)
*/
void Keyboard::setKeyState(const SDL_Keycode &key, const bool &state)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return;
	keyStates[key] = state;
}

/**
* Copies the current key state values into the previous key state values in preperation for a new frame
*/
void Keyboard::swapStates()
{
	for(auto i = KEYCODES_MIN; i <= KEYCODES_MAX; ++i)
	{
		prevKeyStates[i] = keyStates[i];
	}
}

/**
 * Returns true if the specified key is currently down
 * @param key The keycode to poll
 */
bool Keyboard::isKeyDown(const SDL_Keycode &key)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return false;
	return keyStates[key];
}

/**
* Returns true if the specified key is currently down and was up in the previous frame
* @param key The keycode to poll
*/
bool Keyboard::isKeyPressed(const SDL_Keycode &key)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return false;
	return keyStates[key] && !prevKeyStates[key];
}

/**
* Returns true if the specified key is currently up and was down in the previous frame
* @param key The keycode to poll
*/
bool Keyboard::isKeyReleased(const SDL_Keycode &key)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return false;
	return prevKeyStates[key] && !keyStates[key];
}

/**
* Returns true if the specified key is up
* @param key The keycode to poll
*/
bool Keyboard::isKeyUp(const SDL_Keycode &key)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return false;
	return !keyStates[key];
}

/**
* Output keyboard state information to the console
*/
void Keyboard::outputState()
{
	for(auto i = KEYCODES_MIN; i <= KEYCODES_MAX; ++i)
	{
		if(isKeyDown(i) || isKeyReleased(i))
		{
			printf("Key: %c (%d)\n Down: %d, Pressed: %d, Up: %d, Released: %d\n", i, static_cast<char>(i),
				isKeyDown(i), isKeyPressed(i), isKeyUp(i), isKeyReleased(i));
		}
	}
}
