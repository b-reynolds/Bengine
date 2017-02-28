#pragma once
#include <SDL.h>
#include "Rectangle.h"
#include "bengine_typedefs.h"

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
		Vector2f size() const;

		/* Set the Sprite's origin for rendering and rotation */
		void set_origin(const Vector2f &origin);

		/* Returns the Sprite's current point of origin for rendering and rotation */
		Vector2f origin() const;

		/* Set the Sprite's scale */
		void set_scale(const Vector2f &scale);

		/* Returns the Sprite's current scale */
		Vector2f scale() const;

		/* Set the horizontal flip state of the Sprite */
		void set_flipped(const bool &state);

		/* Returns the horizontal flip state of the Sprite */
		SDL_RendererFlip flipped() const;

		/* Returns a pointer to the Sprite's texture */
		SDL_Texture* texture() const;

		/* Returns a pointer to the Sprite's renderer */
		SDL_Renderer* renderer() const;

	 private:

		/* Texture used when the Sprite is rendered */
		SDL_Texture* texture_;

		/* Renderer used to render the Sprite */
		SDL_Renderer* renderer_;

		/* Horizontal flip state of the Sprite*/
		SDL_RendererFlip flipped_;

		/* Sprite's size without scaling factored */
		Vector2f size_;

		/* Sprite's scale */
		Vector2f scale_;

		/* Sprite's point of origin */
		Vector2f origin_;

	};
}
