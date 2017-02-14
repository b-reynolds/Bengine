#pragma once
#include <SDL.h>
#include "Rectangle.h"

namespace BG
{
	class Window;

	class Sprite
	{

	public:

		Sprite();
		Sprite(SDL_Texture* texture, Window* window);

		void setSize(const Vector2i &size);
		void setFlipped(const bool &state);
		void setOrigin(const Vector2f &origin);

		SDL_Texture* getTexture() const;
		SDL_Renderer* getRenderer() const;
		Vector2i getSize() const;
		SDL_RendererFlip getFlipped() const;
		Vector2f getOrigin() const;

	private:

		SDL_Texture* texture;
		SDL_Renderer* renderer;
		SDL_RendererFlip flipped;
		Vector2i size;
		Vector2f origin;


	};
}
