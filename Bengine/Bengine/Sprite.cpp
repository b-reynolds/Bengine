#include "Sprite.h"

BG::Sprite::Sprite()
{
	texture = nullptr;
	renderer = nullptr;
}

BG::Sprite::Sprite(SDL_Texture* texture, SDL_Renderer* renderer)
{
	this->texture = texture;
	this->renderer = renderer;
	SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
}

void BG::Sprite::setSize(const Vector2i& size)
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

BG::Vector2i BG::Sprite::getSize() const
{
	return size;
}

SDL_RendererFlip BG::Sprite::getFlipped() const
{
	return flipped;
}

BG::Vector2f BG::Sprite::getOrigin() const
{
	return origin;
}
