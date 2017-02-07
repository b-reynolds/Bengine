#pragma once
#include <SDL_render.h>

namespace BG
{
	class Renderer
	{

	public:

		static void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, const int &x, const int &y);
		static void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, const int &x, const int &y, const int &width, const int &height);

	};
}

