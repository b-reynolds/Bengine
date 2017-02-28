#pragma once
#include "Audio.h"
#include "transform.h"
#include "colour.h"
#include <string>
#include "Rectangle.h"

namespace BG
{
	// Forward Declaration
	class Window;

	/*
	 * Text Class
	 */
	class Text
	{

	public:

		/* Default Constructor */
		Text();

		/* Initializing Constructor */
		explicit Text(Font* font, const std::string &text, Window* window);

		/* Set the text that is displayed */
		void set_text(const std::string &text);
		
		/* Returns the current text value */
		std::string text() const;

		/* Set the text colour */
		void set_colour(const Colour &colour);
		
		/* Returns the text colour*/
		Colour colour() const;

		/* Set the Text's origin for rendering and rotation */
		void set_origin(const Vector2f &origin);

		/* Returns the Text's current point of origin for rendering and rotations */
		Vector2f origin() const;
		
		/* Creates and returns a texture ready for tendering */
		Texture* texture() const;

		/* Returns a reference to the Text's Transform */
		Transform& transform();

		Vector2f rotate_point(const Vector2f &point, const float &angle);

		FloatRect bounds();

	private:

		/* Text's current transformation */
		Transform transform_;

		/* Text's string value */
		std::string text_;

		/* Font the text renders in */
		Font* font_;

		/* Colour the text renders in */
		Colour colour_;

		/* Window the text renders to */
		Window* window_;

		/* Text's point of origin for rendering and rotations */
		Vector2f origin_;

	};

}

