#pragma once
#include <SDL_render.h>
#include "Vector2.h"

class Sprite;

namespace BG
{
	class Window;
	class GameObject;

	class Renderer
	{

	public:

		static void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, const int &x, const int &y);
		static void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, const int &x, const int &y, const int &width, const int &height);

		static void draw(const GameObject &gameObject, const Window &window);
		static void draw(const GameObject &gameObject);


	};
}

