#include "sprite.h"
#include "window.h"

/*
 * \brief Default Constructor
 */
BG::Sprite::Sprite()
{
	flipped_ = SDL_FLIP_NONE;
	texture_ = nullptr;
	renderer_ = nullptr;
}

/*
 * \brief Initialize the Sprite's Texture and Window
 */
BG::Sprite::Sprite(Texture* texture, Window* window)
{
	this->texture_ = texture;
	this->renderer_ = window->renderer();

	flipped_ = kDefaultFlipState;
	scale_ = Vector2f(kScaleDefault, kScaleDefault);

	int sizeX = 0;
	int sizeY = 0;

	SDL_QueryTexture(texture, nullptr, nullptr, &sizeX, &sizeY);
	size_ = Vector2f(sizeX, sizeY);

	colour_ = kColourDefault;
}

/*
 * \brief Set the size of the Sprite
 * \param size Sprite size
 */
void BG::Sprite::set_size(const Vector2f& size)
{
	this->size_ = size;
}

/*
* \brief Returns the Sprite's current size (scaled)
*/
BG::Vector2f BG::Sprite::size() const
{
	return Vector2f(size_.x_ * scale_.x_, size_.y_ * scale_.y_);
}

/*
* \brief Set the Sprite's scale
*/
void BG::Sprite::set_scale(const Vector2f& scale)
{
	this->scale_ = scale;
}

/*
* \brief Returns the Sprite's current scale
*/
BG::Vector2f BG::Sprite::scale() const
{
	return scale_;
}

void BG::Sprite::set_colour(const Colour& colour)
{
	colour_ = colour;
}

BG::Colour BG::Sprite::colour()
{
	return colour_;
}

/* 
 * \brief Set the horizontal flip state of the Sprite
 * \param state flip state
 */
void BG::Sprite::set_flipped(const bool& state)
{
	flipped_ = state ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}

/*
* \brief Returns the horizontal flip state of the Sprite
*/
SDL_RendererFlip BG::Sprite::flipped() const
{
	return flipped_;
}

/*
 * \brief Returns a pointer to the Sprite's texture
 */
SDL_Texture* BG::Sprite::texture() const
{
	return texture_;
}

/*
 * \brief Returns a pointer to the Sprite's renderer
 */
SDL_Renderer* BG::Sprite::renderer() const
{
	return renderer_;
}