#pragma once
#include <SDL.h>

#define KEYCODES_MIN 0
#define KEYCODES_MAX 255

class Keyboard
{

private:

	static Keyboard *instance;
	Keyboard();

	bool keyStates[KEYCODES_MAX] = { false };
	bool prevKeyStates[KEYCODES_MAX] = { false };

public:

	static Keyboard* getInstance();
	~Keyboard();

	void setKeyState(const SDL_Keycode &key, const bool &state);

	void swapStates();

	bool isKeyDown(const SDL_Keycode &key);
	bool isKeyPressed(const SDL_Keycode &key);
	bool isKeyReleased(const SDL_Keycode &key);
	bool isKeyUp(const SDL_Keycode &key);

	void outputState();

};

