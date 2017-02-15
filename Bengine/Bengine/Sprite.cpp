#include "Sprite.h"
#include "Window.h"

/*
 * \brief Default Constructor
 */
BG::Sprite::Sprite()
{
	flipped = SDL_FLIP_NONE;
	texture = nullptr;
	renderer = nullptr;
}
/*
 * \brief Initialize the Sprite's Texture and Window
 */

BG::Sprite::Sprite(Texture* texture, Window* window)
{
	this->texture = texture;
	this->renderer = window->getRenderer();
	flipped = SDL_FLIP_NONE;
	scale = Vector2f(1.0f, 1.0f);
	int sizeX = 0;
	int sizeY = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &sizeX, &sizeY);
	size = Vector2f(sizeX, sizeY);
}

/*
 * \brief Set the size of the Sprite
 * \param size Sprite size
 */
void BG::Sprite::setSize(const Vector2f& size)
{
	this->size = size;
}

/*
* \brief Returns the Sprite's current size (scaled)
*/
BG::Vector2f BG::Sprite::getSize() const
{
	return Vector2f(size.x * scale.x, size.y * scale.y);
}
/*
* \brief Set the Sprite's origin for rendering and rotation
* \param origin Sprite origin
*/
void BG::Sprite::setOrigin(const Vector2f& origin)
{
	this->origin = origin;
}

/*
* \brief Returns the Sprite's current point of origin for rendering and rotation
*/
BG::Vector2f BG::Sprite::getOrigin() const
{
	return origin;
}

/*
* \brief Set the Sprite's scale
*/
void BG::Sprite::setScale(const Vector2f& scale)
{
	this->scale = scale;
}

/*
* \brief Returns the Sprite's current scale
*/
BG::Vector2f BG::Sprite::getScale() const
{
	return scale;
}

/* 
 * \brief Set the horizontal flip state of the Sprite
 * \param state flip state
 */
void BG::Sprite::setFlipped(const bool& state)
{
	flipped = state ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}

/*
* \brief Returns the horizontal flip state of the Sprite
*/
SDL_RendererFlip BG::Sprite::getFlipped() const
{
	return flipped;
}

/*
 * \brief Returns a pointer to the Sprite's texture
 */
SDL_Texture* BG::Sprite::getTexture() const
{
	return texture;
}

/*
 * \brief Returns a pointer to the Sprite's renderer
 */
SDL_Renderer* BG::Sprite::getRenderer() const
{
	return renderer;
}