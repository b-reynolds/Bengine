#include "ResourceManager.h"
#include "Logger.h"
#include <SDL_image.h>

BG::ResourceManager* BG::ResourceManager::instance = nullptr;

BG::ResourceManager::ResourceManager() {}

/**
 * @brief Returns a SDL_Texture* of the specified size and colour
 * @param r The red vlaue
 * @param g The green value
 * @param b The blue value
 * @param a The alpha value
 * @param renderer The renderer to use
 */
SDL_Texture* BG::ResourceManager::createTexture(const int& size, const unsigned char &r, const unsigned char &g, const unsigned char &b, const unsigned char &a, SDL_Renderer* renderer)
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
	std::map<std::string, SDL_Texture*>::iterator iterator = loadedTextures.begin();
	while(iterator != loadedTextures.end())
	{
		SDL_DestroyTexture(iterator->second);
		iterator = loadedTextures.erase(iterator);
	}

	std::map<std::string, Mix_Chunk*>::iterator iterator2 = loadedSoundEffects.begin();
	while (iterator2 != loadedSoundEffects.end())
	{
		Mix_FreeChunk(iterator2->second);
		iterator2 = loadedSoundEffects.erase(iterator2);
	}

	IMG_Quit();

	std::map<std::string, Mix_Music*>::iterator iterator3 = loadedMusic.begin();
	while (iterator3 != loadedMusic.end())
	{
		Mix_FreeMusic(iterator3->second);
		iterator3 = loadedMusic.erase(iterator3);
	}

	Mix_Quit();

	delete instance;
}

/**
 * @brief Returns the specified SDL_Texture from loadedTextures. If it doesn't yet exist, loads and stores it.
 * @param filePath The file path of the desired image resource
 * @param renderer The renderer to use
 */
SDL_Texture* BG::ResourceManager::getTexture(const std::string &filePath, SDL_Renderer* renderer)
{
	auto result = loadedTextures.find(filePath);
	if (result != loadedTextures.end())
	{
		return result->second;
	}

	auto texture = loadTexture(filePath, renderer);

	if(texture == nullptr)
	{
		texture = createTexture(32, 255, 0, 255, 255, renderer);
	}

	loadedTextures.insert(std::pair<std::string, SDL_Texture*>(filePath, texture));

	return texture;
}

/**
* @brief Returns the specified Mix_Chunk* from the loadedSoundEffects. If it doesn't yet exist, loads and stores it.
* @param filePath The file path of the desired sound resource
*/
Mix_Chunk* BG::ResourceManager::getSoundEffect(const std::string& filePath)
{
	auto result = loadedSoundEffects.find(filePath);
	if(result != loadedSoundEffects.end())
	{
		return result->second;
	}

	auto soundEffect = loadSoundEffect(filePath);
	loadedSoundEffects.insert(std::pair<std::string, Mix_Chunk*>(filePath, soundEffect));

	return soundEffect;
}

/**
* @brief Returns the specified Mix_Chunk* from the loadedMusic. If it doesn't yet exist, loads and stores it.
* @param filePath The file path of the desired sound resource
*/
Mix_Music* BG::ResourceManager::getMusic(const std::string& filePath)
{
	auto result = loadedMusic.find(filePath);
	if (result != loadedMusic.end())
	{
		return result->second;
	}

	auto music = loadMusic(filePath);
	loadedMusic.insert(std::pair<std::string, Mix_Music*>(filePath, music));

	return music;
}

/**
* @brief Load a texture from a file (BMP, GIF, JPEG, LBM, PCX, PNG, PNM, TGA, TIFF, WEBP, XCF, XPM, XV)
* @param filePath The file path of the image
* @param renderer The renderer to upload the image to
*/
SDL_Texture* BG::ResourceManager::loadTexture(const std::string& filePath, SDL_Renderer* renderer)
{
	auto texture = IMG_LoadTexture(renderer, filePath.c_str());
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

/**
* @brief Load a sound effect from a file (WAVE, MOD, MIDI, OGG, MP3)
* @param filePath The file path of the sound
*/
Mix_Chunk* BG::ResourceManager::loadSoundEffect(const std::string& filePath)
{
	auto soundEffect = Mix_LoadWAV(filePath.c_str());
	if (soundEffect != nullptr)
	{
		Logger::getInstance()->log(Logger::INFO, "Loaded \"" + filePath + "\"");
	}
	else
	{
		Logger::getInstance()->log(Logger::ERROR, "Failed to load \"" + filePath + "\"");
	}
	return soundEffect;
}

/**
* @brief Load music from a file (WAVE, MOD, MIDI, OGG, MP3)
* @param filePath The file path of the sound
*/
Mix_Music* BG::ResourceManager::loadMusic(const std::string& filePath)
{
	auto music = Mix_LoadMUS(filePath.c_str());
	if(music != nullptr)
	{
		Logger::getInstance()->log(Logger::INFO, "Loaded \"" + filePath + "\"");
	}
	else
	{
		Logger::getInstance()->log(Logger::ERROR, "Failed to load \"" + filePath + "\"");
	}
	return music;
}

/**
 * @brief Free a texture resource and remove it from the loadedTextures map
 * @param filePath The file path of the image
 */
void BG::ResourceManager::freeTexture(const std::string& filePath)
{
	std::map<std::string, SDL_Texture*>::iterator iterator = loadedTextures.begin();
	while(iterator != loadedTextures.end())
	{
		if(iterator->first == filePath)
		{
			auto texture = iterator->second;
			SDL_DestroyTexture(texture);
			texture = nullptr;
			iterator = loadedTextures.erase(iterator);
		}
		else
		{
			++iterator;
		}
	}
}

/**
* @brief Free a sound effect resource and remove it from the loadedSoundEffects map
* @param filePath The file path of the sound
*/
void BG::ResourceManager::freeSoundEffect(const std::string& filePath)
{
	std::map<std::string, Mix_Chunk*>::iterator iterator = loadedSoundEffects.begin();
	while (iterator != loadedSoundEffects.end())
	{
		if (iterator->first == filePath)
		{
			auto soundEffect = iterator->second;
			Mix_FreeChunk(soundEffect);
			soundEffect = nullptr;
			iterator = loadedSoundEffects.erase(iterator);
		}
		else
		{
			++iterator;
		}
	}
}

/**
* @brief Free a music resource and remove it from the loadedMusic map
* @param filePath The file path of the sound
*/
void BG::ResourceManager::freeMusic(const std::string& filePath)
{
	std::map<std::string, Mix_Music*>::iterator iterator = loadedMusic.begin();
	while (iterator != loadedMusic.end())
	{
		if (iterator->first == filePath)
		{
			auto music = iterator->second;
			Mix_FreeMusic(music);
			music = nullptr;
			iterator = loadedMusic.erase(iterator);
		}
		else
		{
			++iterator;
		}
	}
}
