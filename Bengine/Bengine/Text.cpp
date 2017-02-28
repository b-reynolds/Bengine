#include "Text.h"
#include "window.h"
#include "math.h"

/*
 * \brief Default Constructor
 */
BG::Text::Text()
{
	font_ = nullptr;
	window_ = nullptr;
}

/*
 * \brief Initialize the Text
 * \param font font file to use for rendering
 * \param text text to be displayed
 * \param window window to render to
 */
BG::Text::Text(Font* font, const std::string& text, Window* window)
{
	this->font_ = font;
	this->text_ = text;
	this->window_ = window;
}

/*
 * \brief Set the text that is displayed
 * \brief text text to be displayed
 */
void BG::Text::set_text(const std::string& text)
{
	this->text_ = text;
}

/*
 * \brief Returns the current text value
 */
std::string BG::Text::text() const
{
	return text_;
}

/*
 * \brief Set the text Colour
 * \param colour text Colour
 */
void BG::Text::set_colour(const Colour& colour)
{
	this->colour_ = colour;
}

/*
 * \brief Returns the text Colour
 */
BG::Colour BG::Text::colour() const
{
	return Colour(colour_.r_, colour_.g_, colour_.b_, colour_.a_);
}

/* 
 * \brief Set the Text's origin for rendering and rotations
 * \param origin point of origin
 */
void BG::Text::set_origin(const Vector2f& origin)
{
	this->origin_ = origin;
}

/*
 * \brief Returns the Text's current point of origin for rendering and rotations
 */
BG::Vector2f BG::Text::origin() const
{
	return origin_;
}

/*
 * Creates and returns a texture ready for rendering 
 */
BG::Texture* BG::Text::texture() const
{
	SDL_Color txtColour;

	txtColour.r = colour_.r_;
	txtColour.g = colour_.g_;
	txtColour.b = colour_.b_;
	txtColour.a = colour_.a_;

	SDL_Surface* surface = TTF_RenderText_Blended(font_, text_.c_str(), txtColour);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(window_->renderer(), surface);

	SDL_FreeSurface(surface);

	return texture;
}

/*
 * Returns a reference to the Text's Transform
 */
BG::Transform& BG::Text::transform() 
{
	return transform_;
}

BG::Vector2f BG::Text::rotate_point(const Vector2f &point, const float &angle)
{
	float theta = Math::degreesToRadians(angle);
	BG::Vector2f newPoint;


	newPoint.x_ = point.x_ * cos(theta) - point.y_ * sin(theta);
	newPoint.y_ = point.x_ * sin(theta) + point.y_ * cos(theta);

	return newPoint;


}


BG::FloatRect BG::Text::bounds()
{
	Vector2i size;
	Vector2f position = transform().position();
	TTF_SizeText(font_, text_.c_str(), &size.x_, &size.y_);

	Vector2f topLeft(position.x_, position.y_);
	Vector2f topRight(position.x_ + size.x_, position.y_);
	Vector2f bottomLeft(position.x_, position.y_ + size.y_);
	Vector2f bottomRight(position.x_ + size.x_, position.y_ + size.y_);

	float angle = transform_.rotation();

	topLeft = rotate_point(topLeft, angle);
	topRight = rotate_point(topRight, angle);
	bottomLeft = rotate_point(bottomLeft, angle);
	bottomRight = rotate_point(bottomRight, angle);


	return FloatRect(topLeft.x_, topLeft.y_, topRight.x_ - topLeft.x_, bottomRight.y_ - topRight.y_);
}
