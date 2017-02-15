#include "Sprite.h"
#include "Window.h"

BG::Sprite::Sprite()
{
	texture = nullptr;
	renderer = nullptr;
}

BG::Sprite::Sprite(SDL_Texture* texture, Window* window)
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

void BG::Sprite::setSize(const Vector2f& size)
{
	this->size = size;
}

void BG::Sprite::setFlipped(const bool& state)
{
	flipped = state ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}

void BG::Sprite::setOrigin(const Vector2f& origin)
{
	this->origin = origin;
}

SDL_Texture* BG::Sprite::getTexture() const
{
	return texture;
}

SDL_Renderer* BG::Sprite::getRenderer() const
{
	return renderer;
}

BG::Vector2f BG::Sprite::getSize() const
{
	return Vector2f(size.x * scale.x, size.y * scale.y);
}

SDL_RendererFlip BG::Sprite::getFlipped() const
{
	return flipped;
}

BG::Vector2f BG::Sprite::getOrigin() const
{
	return origin;
}

void BG::Sprite::setScale(const Vector2f& scale)
{
	this->scale = scale;
}

BG::Vector2f BG::Sprite::getScale() const
{
	return scale;
}
