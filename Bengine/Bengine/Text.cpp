#include "Text.h"
#include "Window.h"

/*
 * \brief Default Constructor
 */
BG::Text::Text()
{
	font = nullptr;
	window = nullptr;
}

/*
 * \brief Initialize the Text
 * \param font font file to use for rendering
 * \param text text to be displayed
 * \param window window to render to
 */
BG::Text::Text(Font* font, const std::string& text, Window* window)
{
	this->font = font;
	this->text = text;
	this->window = window;
}

/*
 * \brief Set the text that is displayed
 * \brief text text to be displayed
 */
void BG::Text::setText(const std::string& text)
{
	this->text = text;
}

/*
 * \brief Returns the current text value
 */
std::string BG::Text::getText() const
{
	return text;
}

/*
 * \brief Set the text Colour
 * \param colour text Colour
 */
void BG::Text::setColour(const Colour& colour)
{
	this->colour = colour;
}

/*
 * \brief Returns the text Colour
 */
BG::Colour BG::Text::getColour() const
{
	return Colour(colour.r, colour.g, colour.b, colour.a);
}

/* 
 * \brief Set the Text's origin for rendering and rotations
 * \param origin point of origin
 */
void BG::Text::setOrigin(const Vector2f& origin)
{
	this->origin = origin;
}

/*
 * \brief Returns the Text's current point of origin for rendering and rotations
 */
BG::Vector2f BG::Text::getOrigin() const
{
	return origin;
}

/*
 * Creates and returns a texture ready for rendering 
 */
BG::Texture* BG::Text::getTexture() const
{
	SDL_Color txtColour;

	txtColour.r = colour.r;
	txtColour.g = colour.g;
	txtColour.b = colour.b;
	txtColour.a = colour.a;

	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), txtColour);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(window->getRenderer(), surface);

	SDL_FreeSurface(surface);

	return texture;
}

/*
 * Returns a reference to the Text's Transform
 */
BG::Transform& BG::Text::getTransform() 
{
	return transform;
}
