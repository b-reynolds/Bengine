#include "ResourceManager.h"
#include "Logger.h"
#include <SDL_image.h>

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager::ResourceManager() {}

/**
 * @brief Returns a SDL_Texture* of the specified size and colour
 * @param r The red vlaue
 * @param g The green value
 * @param b The blue value
 * @param a The alpha value
 * @param renderer The renderer to use
 */
SDL_Texture* ResourceManager::createTexture(const int& size, const unsigned char &r, const unsigned char &g, const unsigned char &b, const unsigned char &a, SDL_Renderer* renderer)
{
	auto myInt = 1;
	auto myString = "HELLO";

	auto texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, size, size);
	unsigned char* bytes = nullptr;
	int pitch = 0;
	SDL_LockTexture(texture, nullptr, reinterpret_cast<void**>(&bytes), &pitch);
	unsigned char rgba[4] = { a, b, g, r };
	for (int y = 0; y < size; ++y)
	{
		for (int x = 0; x < size; ++x)
		{
			memcpy(&bytes[(y * size + x) * sizeof(rgba)], rgba, sizeof(rgba));
		}
	}
	SDL_UnlockTexture(texture);
	return texture;
}

/**
* @brief Returns a pointer to a singleton instance of the Logger class
*/
ResourceManager* ResourceManager::getInstance()
{
	if(instance == nullptr)
	{
		instance = new ResourceManager();
	}
	return instance;
}

/** Deconstructor
* Delete dynamically memory
*/
ResourceManager::~ResourceManager()
{
	std::map<std::string, SDL_Texture*>::iterator iterator = textureMap.begin();
	while(iterator != textureMap.end())
	{
		delete iterator->second;
		++iterator;
	}
	delete instance;
}

/**
 * @brief Returns the specified SDL_Texture from the textureMap. If it doesn't yet exist, loads and stores it.
 * @param filePath The file path of the desired image resource
 * @param renderer The renderer to use
 */
SDL_Texture* ResourceManager::getTexture(const std::string &filePath, SDL_Renderer* renderer)
{
	auto result = textureMap.find(filePath);
	if (result != textureMap.end())
	{
		return result->second;
	}

	auto texture = loadTexture(filePath, renderer);

	if(texture == nullptr)
	{
		texture = createTexture(32, 255, 0, 255, 255, renderer);
	}

	textureMap.insert(std::pair<std::string, SDL_Texture*>(filePath, texture));

	return texture;
}

/**
* Load a texture from an image file (BMP, GIF, JPEG, LBM, PCX, PNG, PNM, TGA, TIFF, WEBP, XCF, XPM, XV)
* @param filePath The file path of the image
* @param renderer The renderer to upload the image to
*/
SDL_Texture* ResourceManager::loadTexture(const std::string& filePath, SDL_Renderer* renderer)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
	if(texture != nullptr)
	{
		Logger::getInstance()->log(Logger::INFO, "Loaded \"" + filePath + "\"");
	}
	else
	{
		Logger::getInstance()->log(Logger::ERROR, "Failed to load \"" + filePath + "\"");
	}
	return texture;
}
