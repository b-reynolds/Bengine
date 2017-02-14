#include "Keyboard.h"
#include "Logger.h"

BG::Keyboard* BG::Keyboard::instance = nullptr;

BG::Keyboard::Keyboard() { }

/**
* Returns a pointer to the singleton instance of the Keyboard class
*/
BG::Keyboard* BG::Keyboard::getInstance()
{
	if(instance == nullptr)
	{
		instance = new Keyboard();
	}
	return instance;
}

BG::Keyboard::~Keyboard()
{
	printf("Keyboard deconstructing..\n");
}

/**
* Set the current state of a key
* @param key The keycode to set
* @param state The state of the key (True = Down, False = Up)
*/
void BG::Keyboard::setKeyState(const SDL_Keycode &key, const bool &state)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return;
	keyStates[key] = state;
	if (prevKeyStates[key] != keyStates[key])
	{
		Logger::getInstance()->log(Logger::DEBUG, std::string("Key (") +
			std::to_string(key) + "/" + static_cast<char>(key) + ") State: " + (state ? "Down" : "Up"));
	}
}

/**
* Copies the current key state values into the previous key state values in preperation for a new frame
*/
void BG::Keyboard::swapStates() // TODO: Rename?
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
bool BG::Keyboard::isKeyDown(const SDL_Keycode &key)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return false;
	return keyStates[key];
}

/**
* Returns true if the specified key is currently down and was up in the previous frame
* @param key The keycode to poll
*/
bool BG::Keyboard::isKeyPressed(const SDL_Keycode &key)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return false;
	return keyStates[key] && !prevKeyStates[key];
}

/**
* Returns true if the specified key is currently up and was down in the previous frame
* @param key The keycode to poll
*/
bool BG::Keyboard::isKeyReleased(const SDL_Keycode &key)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return false;
	return prevKeyStates[key] && !keyStates[key];
}

/**
* Returns true if the specified key is up
* @param key The keycode to poll
*/
bool BG::Keyboard::isKeyUp(const SDL_Keycode &key)
{
	if (key < KEYCODES_MIN || key > KEYCODES_MAX) return false;
	return !keyStates[key];
}
