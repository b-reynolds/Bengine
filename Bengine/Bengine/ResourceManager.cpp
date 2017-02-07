#include "ResourceManager.h"
#include "Logger.h"
#include <SDL_image.h>

BG::ResourceManager* BG::ResourceManager::instance = nullptr;

BG::ResourceManager::ResourceManager() {}

/**
 * @brief Returns a SDL_Texture* of the specified size and colour
 * @param r The red value
 * @param g The green value
 * @param b The blue value
 * @param a The alpha value
 * @param renderer The renderer to use
 */
SDL_Texture* BG::ResourceManager::createTexture(const int &size, const unsigned char &r, const unsigned char &g, const unsigned char &b, const unsigned char &a, SDL_Renderer* renderer)
{
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
BG::ResourceManager* BG::ResourceManager::getInstance()
{
	if(instance == nullptr)
	{
		instance = new ResourceManager();
	}
	return instance;
}

/** Deconstructor
* Free dynamically memory
*/
BG::ResourceManager::~ResourceManager()
{
	std::map<std::string, SDL_Texture*>::iterator iterator = mpTextures.begin();
	while(iterator != mpTextures.end())
	{
		SDL_DestroyTexture(iterator->second);
		iterator = mpTextures.erase(iterator);
	}

	std::map<std::string, Mix_Chunk*>::iterator iterator2 = mpSoundEffects.begin();
	while (iterator2 != mpSoundEffects.end())
	{
		Mix_FreeChunk(iterator2->second);
		iterator2 = mpSoundEffects.erase(iterator2);
	}

	IMG_Quit();

	std::map<std::string, Mix_Music*>::iterator iterator3 = mpMusic.begin();
	while (iterator3 != mpMusic.end())
	{
		Mix_FreeMusic(iterator3->second);
		iterator3 = mpMusic.erase(iterator3);
	}

	Mix_Quit();

	delete instance;
}

/**
 * @brief Returns the specified SDL_Texture from mpTextures. If it doesn't yet exist, loads and stores it.
 * @param filePath The file path of the desired image resource
 * @param renderer The renderer to use
 */
SDL_Texture* BG::ResourceManager::getTexture(const std::string &filePath, SDL_Renderer* renderer)
{
	auto result = mpTextures.find(filePath);
	if (result != mpTextures.end())
	{
		return result->second;
	}

	auto texture = loadTexture(filePath, renderer);

	if(texture == nullptr)
	{
		texture = createTexture(32, 255, 0, 255, 255, renderer);
	}

	mpTextures.insert(std::pair<std::string, SDL_Texture*>(filePath, texture));

	return texture;
}

/**
* @brief Returns the specified Mix_Chunk* from the mpSoundEffects. If it doesn't yet exist, loads and stores it.
* @param filePath The file path of the desired sound resource
*/
Mix_Chunk* BG::ResourceManager::getSoundEffect(const std::string &filePath)
{
	auto result = mpSoundEffects.find(filePath);
	if(result != mpSoundEffects.end())
	{
		return result->second;
	}

	auto soundEffect = loadSoundEffect(filePath);
	mpSoundEffects.insert(std::pair<std::string, Mix_Chunk*>(filePath, soundEffect));

	return soundEffect;
}

/**
* @brief Returns the specified Mix_Chunk* from the mpMusic. If it doesn't yet exist, loads and stores it.
* @param filePath The file path of the desired sound resource
*/
Mix_Music* BG::ResourceManager::getMusic(const std::string &filePath)
{
	auto result = mpMusic.find(filePath);
	if (result != mpMusic.end())
	{
		return result->second;
	}

	auto music = loadMusic(filePath);
	mpMusic.insert(std::pair<std::string, Mix_Music*>(filePath, music));

	return music;
}

/**
* @brief Load a texture from a file (BMP, GIF, JPEG, LBM, PCX, PNG, PNM, TGA, TIFF, WEBP, XCF, XPM, XV)
* @param filePath The file path of the image
* @param renderer The renderer to upload the image to
*/
SDL_Texture* BG::ResourceManager::loadTexture(const std::string &filePath, SDL_Renderer* renderer)
{
	auto texture = IMG_LoadTexture(renderer, filePath.c_str());
	if(texture != nullptr)
	{
		Logger::getInstance()->log(Logger::INFO, "Loaded \"" + filePath + "\"");
	}
	else
	{
		Logger::getInstance()->log(Logger::ERROR, "Failed to load \"" + filePath + "\" (" + IMG_GetError() + ")");
	}
	return texture;
}

/**
* @brief Load a sound effect from a file (WAVE, MOD, MIDI, OGG, MP3)
* @param filePath The file path of the sound
*/
Mix_Chunk* BG::ResourceManager::loadSoundEffect(const std::string &filePath)
{
	auto soundEffect = Mix_LoadWAV(filePath.c_str());
	if (soundEffect != nullptr)
	{
		Logger::getInstance()->log(Logger::INFO, "Loaded \"" + filePath + "\"");
	}
	else
	{
		Logger::getInstance()->log(Logger::ERROR, "Failed to load \"" + filePath + "\" (" + Mix_GetError() + ")");
	}
	return soundEffect;
}

/**
* @brief Load music from a file (WAVE, MOD, MIDI, OGG, MP3)
* @param filePath The file path of the sound
*/
Mix_Music* BG::ResourceManager::loadMusic(const std::string &filePath)
{
	auto music = Mix_LoadMUS(filePath.c_str());
	if(music != nullptr)
	{
		Logger::getInstance()->log(Logger::INFO, "Loaded \"" + filePath + "\"");
	}
	else
	{
		Logger::getInstance()->log(Logger::ERROR, "Failed to load \"" + filePath + "\" (" + Mix_GetError() + ")");
	}
	return music;
}

/**
 * @brief Free a texture resource and remove it from the mpTextures map
 * @param filePath The file path of the image
 */
void BG::ResourceManager::freeTexture(const std::string &filePath)
{
	std::map<std::string, SDL_Texture*>::iterator iterator = mpTextures.begin();
	while(iterator != mpTextures.end())
	{
		if(iterator->first == filePath)
		{
			auto texture = iterator->second;
			SDL_DestroyTexture(texture);
			texture = nullptr;
			Logger::getInstance()->log(Logger::INFO, "Freed resource \"" + iterator->first + "\"");
			iterator = mpTextures.erase(iterator);
			break;
		}
		++iterator;
	}
}

/**
* @brief Free a sound effect resource and remove it from the mpSoundEffects map
* @param filePath The file path of the sound
*/
void BG::ResourceManager::freeSoundEffect(const std::string &filePath)
{
	std::map<std::string, Mix_Chunk*>::iterator iterator = mpSoundEffects.begin();
	while (iterator != mpSoundEffects.end())
	{
		if (iterator->first == filePath)
		{
			auto soundEffect = iterator->second;
			Mix_FreeChunk(soundEffect);
			soundEffect = nullptr;
			Logger::getInstance()->log(Logger::INFO, "Freed resource \"" + iterator->first + "\"");
			iterator = mpSoundEffects.erase(iterator);
			break;
		}
		++iterator;
	}
}

/**
* @brief Free a music resource and remove it from the mpMusic map
* @param filePath The file path of the sound
*/
void BG::ResourceManager::freeMusic(const std::string &filePath)
{
	std::map<std::string, Mix_Music*>::iterator iterator = mpMusic.begin();
	while (iterator != mpMusic.end())
	{
		if (iterator->first == filePath)
		{
			auto music = iterator->second;
			Mix_FreeMusic(music);
			music = nullptr;
			Logger::getInstance()->log(Logger::INFO, "Freed resource \"" + iterator->first + "\"");
			iterator = mpMusic.erase(iterator);
			break;
		}
		++iterator;
	}
}
