#include "Renderer.h"
#include "Vector2D.h"

/**
* Draw a texture to the renderer at the specified position
* @param texture The source texture
* @param renderer The renderer to draw to
* @param x The x coordinate in pixels
* @param y The y coordinate in pixels
*/
void Renderer::renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, const int& x, const int& y)
{
	// Query the texture's width and height
	auto textureSize = Vector2D<int>(0, 0);
	SDL_QueryTexture(texture, nullptr, nullptr, &textureSize.x, &textureSize.y);

	// Render the texture
	renderTexture(texture, renderer, x, y, textureSize.x, textureSize.y);
}

/**
* Draw a texture to the renderer at the specified size and position
* @param texture The source texture
* @param renderer The renderer to draw to
* @param x The x coordinate in pixels
* @param y The y coordinate in pixels
* @param width The width of the texture in pixels
* @param height The height of the texture in pixels
*/
void Renderer::renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, const int &x, const int &y, const int &width, const int &height)
{
	// Create a destionation rectangle
	SDL_Rect destination;

	// Set the rectangles position and size
	destination.x = x;
	destination.y = y;
	destination.w = width;
	destination.h = height;

	// Render the texture at the destination rectangle
	SDL_RenderCopy(renderer, texture, nullptr, &destination);
}
