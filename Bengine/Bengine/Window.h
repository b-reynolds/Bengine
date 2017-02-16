#pragma once
#include "Vector2.h"
#include "Rectangle.h"
#include <SDL.h>
#include <string>

namespace BG
{
	class Text;
	// Forward Declarations
	struct Colour;
	class GameObject;

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

		/* Updates the windows contents post rendering */
		void display() const;

		/* Destroys the window and renderer freeing all associated memory */
		void destroy();

		/* Render Text to the window */		
		void draw(Text &text);

		/* Render a GameObject to the window */
		void draw(GameObject &gameObject) const;

		/* Render a GameObject to the window tinted with the specified Colour */
		void draw(GameObject &gameObject, const Colour &tint) const;

		/* Render a FloatRect of the specified Colour to the window */
		void draw(const FloatRect &rect, const Colour &colour) const;

		/* Set the Window's position */
		void setPosition(const Vector2i &position) const;

		/* Returns the Window's current position */
		Vector2i getPosition() const;

		/* Set the Window's size */
		void setSize(const Vector2i &size) const;

		/* Returns the Window's current size */
		Vector2i getSize() const; 

		/* Set the fullscreen state of the Window */
		void setFullscreen(const bool &state) const;

		/* Set the Window's title */
		void setTitle(const std::string &title) const;

		/* Returns a reference to the Window's renderer */
		SDL_Renderer* getRenderer() const;

		/* Returns true if the Window and its renderer initialized successfully */
		bool isOpen() const;

	private:

		/* The window that is rendered to */
		SDL_Window* window;

		/* Used for drawing/rendering to the window */
		SDL_Renderer* renderer;

	};
}

