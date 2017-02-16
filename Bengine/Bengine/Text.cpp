#include "Text.h"
#include "Window.h"
#include "Math.h"

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

BG::Vector2f BG::Text::rotatePoint(const Vector2f &point, const float &angle)
{
	float theta = Math::degreesToRadians(angle);
	BG::Vector2f newPoint;


	newPoint.x = point.x * cos(theta) - point.y * sin(theta);
	newPoint.y = point.x * sin(theta) + point.y * cos(theta);

	return newPoint;


}


BG::FloatRect BG::Text::getBounds()
{
	Vector2i size;
	Vector2f position = getTransform().getPosition();
	TTF_SizeText(font, text.c_str(), &size.x, &size.y);

	Vector2f topLeft(position.x, position.y);
	Vector2f topRight(position.x + size.x, position.y);
	Vector2f bottomLeft(position.x, position.y + size.y);
	Vector2f bottomRight(position.x + size.x, position.y + size.y);

	float angle = transform.getRotation();

	topLeft = rotatePoint(topLeft, angle);
	topRight = rotatePoint(topRight, angle);
	bottomLeft = rotatePoint(bottomLeft, angle);
	bottomRight = rotatePoint(bottomRight, angle);


	return FloatRect(topLeft.x, topLeft.y, topRight.x - topLeft.x, bottomRight.y - topRight.y);
}
