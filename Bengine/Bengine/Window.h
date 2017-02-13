#pragma once
#include <SDL.h>
#include "Vector2.h"
#include <string>

namespace BG
{
	struct Colour;
	class GameObject;

	class Window
	{

	public:

		Window(const std::string &title, const Vector2u &size);

		void clear() const;
		void display() const;
		void destroy();
		
		void draw(GameObject &gameObject) const;
		void draw(GameObject &gameObject, const Colour &tint) const; 

		void setPosition(const Vector2i &position) const;
		Vector2i getPosition() const;

		void setSize(const Vector2i &size) const;
		Vector2i getSize() const; 

		void setFullscreen(const bool &state) const;
		void setTitle(const std::string &title) const;

		SDL_Renderer* getRenderer() const;


		bool isOpen() const;

	private:

		SDL_Window* window;
		SDL_Renderer* renderer;

	};
}

