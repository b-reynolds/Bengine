#include "ResourceManager.h"
#include "Logger.h"

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager::ResourceManager()
{
}

ResourceManager* ResourceManager::getInstance()
{
	if(instance == nullptr)
	{
		instance = new ResourceManager();
	}
	return instance;
}

ResourceManager::~ResourceManager()
{
	delete instance;
}

/**
* Load a texture from a BMP file
* @param filePath The file path of the bitmap image
* @param renderer The renderer to upload the image to
*/
SDL_Texture* ResourceManager::loadTexture(const std::string& filePath, SDL_Renderer* renderer)
{
	// Create a texture and initialize it to NULL
	SDL_Texture *texture = nullptr;

	// Load in a bitmap image using the specified path
	SDL_Surface *image = SDL_LoadBMP(filePath.c_str());

	if (image != nullptr)
	{
		// Upload the image to the texture
		texture = SDL_CreateTextureFromSurface(renderer, image);

		// Free the image
		SDL_FreeSurface(image);

		if (texture == nullptr)
		{
			// Texture creation failed, report error and return NULL.
			Logger::logSDLError("Failed to create texture");
		}
	}
	else
	{
		// Image loading failed, report error and return NULL.
		Logger::logSDLError("Failed to load bitmap");
	}
	return texture;
}
