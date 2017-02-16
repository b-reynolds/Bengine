#pragma once
#include "Window.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Text.h"

class Game
{

public:

	bool run(BG::Window* window);

	void exit();

private:

	const int SPEED = 250;

	BG::Text myText;
	BG::Text myOtherText;

	BG::Sprite sprLogo;
	BG::GameObject objLogo;

	BG::Window* window;

	bool initialized;

	bool initialize();

	bool update();

	void draw();

};

