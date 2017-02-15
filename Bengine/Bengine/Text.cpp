#include "Text.h"
#include "Colour.h"
#include "Window.h"

BG::Text::Text()
{
}

BG::Text::Text(Font* font, const std::string& text, const Colour &colour, Window* window)
{
	this->font = font;
	this->text = text;

	this->colour.r = colour.r;
	this->colour.g = colour.g;
	this->colour.b = colour.b;
	this->colour.a = colour.a;

	this->window = window;
}

BG::Texture* BG::Text::getTexture() const
{
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), colour);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(window->getRenderer(), surface);
	SDL_FreeSurface(surface);
	return texture;
}
