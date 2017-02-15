#pragma once
#include "Audio.h"
#include <string>

namespace BG
{
	class Window;
	struct Colour;

	class Text
	{

	public:

		Text();
		explicit Text(Font* font, const std::string &text, const Colour &colour, Window* window);
		
		Texture* getTexture() const;


		std::string text;
		Font* font;
		SDL_Colour colour;
		Window* window;

	};

}

