#include "Renderer.h"

/**
* Draw a texture to the renderer at the specified position
* @param texture The source texture
* @param renderer The renderer to draw to
* @param x The x coordinate in pixels
* @param y The y coordinate in pixels
*/
void Renderer::renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, const int& x, const int& y)
{
	// Create a destionation rectangle
	SDL_Rect destination;

	// Set the rectangles position
	destination.x = x;
	destination.y = y;

	// Query the texture's width and height
	SDL_QueryTexture(texture, nullptr, nullptr, &destination.w, &destination.h);

	// Render the texture at the destination rectangle
	SDL_RenderCopy(renderer, texture, nullptr, &destination);
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
void Renderer::renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, const int& x, const int& y, const int& width, const int& height)
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
