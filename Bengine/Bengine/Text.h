#pragma once
#include "Audio.h"
#include "Transform.h"
#include "Colour.h"
#include <string>

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
		void setText(const std::string &text);
		
		/* Returns the current text value */
		std::string getText() const;

		/* Set the text colour */
		void setColour(const Colour &colour);
		
		/* Returns the text colour*/
		Colour getColour() const;

		/* Set the Text's origin for rendering and rotation */
		void setOrigin(const Vector2f &origin);

		/* Returns the Text's current point of origin for rendering and rotations */
		Vector2f getOrigin() const;
		
		/* Creates and returns a texture ready for tendering */
		Texture* getTexture() const;

		/* Returns a reference to the Text's Transform */
		Transform& getTransform();

	private:

		/* Text's current transformation */
		Transform transform;

		/* Text's string value */
		std::string text;

		/* Font the text renders in */
		Font* font;

		/* Colour the text renders in */
		Colour colour;

		/* Window the text renders to */
		Window* window;

		/* Text's point of origin for rendering and rotations */
		Vector2f origin;

	};

}

