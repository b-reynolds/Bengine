#pragma once
#include <SDL.h>
#include "Rectangle.h"
#include "BengineTypedefs.h"

namespace BG
{
	// Forward Declaration
	class Window;

	/*
	 * \brief Sprite Class
	 */
	class Sprite
	{

	public:

		/* Default Constructor */
		Sprite();

		/* Initialize the Sprite's Texture and Window */
		Sprite(Texture* texture, Window* window);

		/* Set the size of the Sprite */
		void setSize(const Vector2f &size);

		/* Returns the Sprite's current size (scaled) */
		Vector2f getSize() const;

		/* Set the Sprite's origin for rendering and rotation */
		void setOrigin(const Vector2f &origin);

		/* Returns the Sprite's current point of origin for rendering and rotation */
		Vector2f getOrigin() const;

		/* Set the Sprite's scale */
		void setScale(const Vector2f &scale);

		/* Returns the Sprite's current scale */
		Vector2f getScale() const;

		/* Set the horizontal flip state of the Sprite */
		void setFlipped(const bool &state);

		/* Returns the horizontal flip state of the Sprite */
		SDL_RendererFlip getFlipped() const;

		/* Returns a pointer to the Sprite's texture */
		SDL_Texture* getTexture() const;

		/* Returns a pointer to the Sprite's renderer */
		SDL_Renderer* getRenderer() const;

	private:

		/* Texture used when the Sprite is rendered */
		SDL_Texture* texture;

		/* Renderer used to render the Sprite */
		SDL_Renderer* renderer;

		/* Horizontal flip state of the Sprite*/
		SDL_RendererFlip flipped;

		/* Sprite's size without scaling factored */
		Vector2f size;

		/* Sprite's scale */
		Vector2f scale;

		/* Sprite's point of origin */
		Vector2f origin;

	};
}
