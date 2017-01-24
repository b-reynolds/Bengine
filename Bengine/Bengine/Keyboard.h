#pragma once
#include <SDL.h>

#define KEYCODE_MIN 0
#define KEYCODE_MAX 255

class Keyboard
{

private:

	static Keyboard *instance;
	Keyboard();

	bool keyStates[KEYCODE_MAX] = { false };
	bool prevKeyStates[KEYCODE_MAX] = { false };

public:

	static Keyboard* getInstance();
	~Keyboard();

	void setKeyState(const SDL_Keycode &key, const bool &state);

	void swapStates();

	bool isKeyDown(const SDL_Keycode &key);
	bool isKeyPressed(const SDL_Keycode &key);
	bool isKeyReleased(const SDL_Keycode &key);
	bool isKeyUp(const SDL_Keycode &key);

};

