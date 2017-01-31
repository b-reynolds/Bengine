#include "ResourceManager.h"
#include "Logger.h"
#include <SDL_image.h>

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
* Load a texture from an image file (BMP, GIF, JPEG, LBM, PCX, PNG, PNM, TGA, TIFF, WEBP, XCF, XPM, XV)
* @param filePath The file path of the image
* @param renderer The renderer to upload the image to
*/
SDL_Texture* ResourceManager::loadTexture(const std::string& filePath, SDL_Renderer* renderer)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, filePath.c_str());
	if (texture == nullptr)
	{
		// Texture creation failed, report error and return NULL.
		Logger::getInstance()->log(Logger::ERROR, "Failed to load texture");
	}
	return texture;
}
