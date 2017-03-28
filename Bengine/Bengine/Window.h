#pragma once
#include "Vector2.h"
#include "Rectangle.h"
#include <SDL.h>
#include <string>
#include "colour.h"
#include "button.h"

namespace BG
{
	// Forward Declarations
	class Text;
	class GameObject;
	struct Colour;

	/*
	 * \brief Windowing Class
	 * A wrapper for SDL_Window
	 */
	class Window
	{

	public:

		/* Creates and initializes a window with the specified title and of the specified size */
		Window(const std::string &title, const Vector2u &size);

		/* Clears the Window's renderer ignoring the viewport and clip rectangle */
		void clear() const;

		/* Sets the clear colour of the window */
		void set_clear_colour(const Colour& colour);

		/* Updates the windows contents post rendering */
		void display() const;

		/* Destroys the window and renderer freeing all associated memory */
		void destroy();

		/* Render Text to the window */		
		void draw(Text &text) const;

		/* Render a GameObject to the window */
		void draw(GameObject &game_object) const;

		/* Render a GameObject to the window tinted with the specified Colour */
		void draw(GameObject &game_object, const Colour &tint) const;

		/* Render a FloatRect of the specified Colour to the window */
		void draw(const FloatRect &rect, const Colour &colour) const;

		/* Render a button to the window */
		void draw(Button& button);

		/* Set the Window's position */
		void set_position(const Vector2i &position) const;

		/* Returns the Window's current position */
		Vector2i position() const;

		/* Set the Window's size */
		void set_size(const Vector2i &size) const;

		/* Returns the Window's current size */
		Vector2i size() const; 

		/* Set the fullscreen state of the Window */
		void set_fullscreen(const bool &state) const;

		/* Set the Window's title */
		void set_title(const std::string &title) const;

		/* Returns a reference to the Window's renderer */
		SDL_Renderer* renderer() const;

		/* Returns true if the Window and its renderer initialized successfully */
		bool open() const;

	private:

		/* The window that is rendered to */
		SDL_Window* window_;

		/* Used for drawing/rendering to the window */
		SDL_Renderer* renderer_;

		/* The clear colour of the window */
		Colour clr_background_;

	};
}

