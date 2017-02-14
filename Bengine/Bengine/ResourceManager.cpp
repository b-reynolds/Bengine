#include "ResourceManager.h"
#include "Logger.h"
#include "Window.h"
#include "Bengine.h"
#include "Colour.h"
#include <SDL_image.h>

// Initialize static members
BG::ResourceManager* BG::ResourceManager::instance = nullptr;

/**
* \brief Default Constructor
*/
BG::ResourceManager::ResourceManager()
{
	
}

/**
 * \brief Frees dynamically allocated memory and unloads dependencies.
 */
BG::ResourceManager::~ResourceManager()
{
	free();
}

/**
* \brief Returns a pointer to the singleton instance of the ResourceManager class.
*/
BG::ResourceManager* BG::ResourceManager::getInstance()
{
	if(instance == nullptr)
	{
		instance = new ResourceManager();
	}
	return instance;
}

/** \brief Loads an image resource into a Texture and returns it.
* Searches the ResourceManager's map of textures for the specified texture and returns a reference to it.
* If the texture does not exist, loads it into memory and stores it in the map.
* If the the texture fails to load, creates a placeholder texture in its place.
* \param filePath file path of the desired image resource
* \param window window the texture will be rendered to
*/
BG::Texture* BG::ResourceManager::getTexture(const std::string& filePath, Window* window)
{
	// Search the map of existing textures for the requested texture
	auto result = mpTextures.find(filePath);

	if (result != mpTextures.end())
	{
		// The texture exists and is already loaded into memory, return a reference to it
		return result->second;
	}

	// Attempt to load the image resource into memory
	Texture* texture = loadTexture(filePath, window);

	if (texture == nullptr)
	{
		// The texture failed to load, create a placeholder texture
		texture = createTexture(TEXTURE_SIZE_DEFAULT, TEXTURE_COLOUR_DEFAULT, window);
	}

	// Insert the texture into the textures map
	mpTextures.insert(std::pair<std::string, Texture*>(filePath, texture));

	return texture;
}

/**
* \brief Free the memory associated with an image resource and remove it from the textures map.
* Iterates through the textures map, if a resource with the same file path is found, frees all associated memory and nullifies the pointer.
* \param filePath file path of the image resource
*/
void BG::ResourceManager::freeTexture(const std::string &filePath)
{
	std::map<std::string, SDL_Texture*>::iterator iterator = mpTextures.begin();
	while (iterator != mpTextures.end())
	{
		if (iterator->first == filePath)
		{
			auto texture = iterator->second;
			SDL_DestroyTexture(texture);
			texture = nullptr;
			Logger::getInstance().log(Logger::INFO, "Freed resource \"" + iterator->first + "\"");
			iterator = mpTextures.erase(iterator);
			break;
		}
		++iterator;
	}
}

/** \brief Loads a sound resource into a SoundEffect and returns it.
* Searches the ResourceManager's map of sound effects for the specified sound effect and returns a reference to it.
* If the sound effect does not exist, loads it into memory and stores it in the map.
* \param filePath file path of the desired sound resource
*/
BG::SoundEffect* BG::ResourceManager::getSoundEffect(const std::string &filePath)
{
	// Search the map of existing sound effects for the requested sound effect
	auto result = mpSoundEffects.find(filePath);

	if (result != mpSoundEffects.end())
	{
		// The sound effect exists and is already loaded into memory, return a reference to it
		return result->second;
	}

	// Attempt to load the sound resource into memory
	SoundEffect* soundEffect = loadSoundEffect(filePath);

	// Insert the sound effect into the sound effects map
	mpSoundEffects.insert(std::pair<std::string, Mix_Chunk*>(filePath, soundEffect));

	return soundEffect;
}

/**
* \brief Free the memory associated with a sound effect resource and remove it from the sound effects map.
* Iterates through the sound effects map, if a resource with the same file path is found, frees all associated memory and nullifies the pointer.
* \param filePath file path of the sound resource
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
			Logger::getInstance().log(Logger::INFO, "Freed resource \"" + iterator->first + "\"");
			iterator = mpSoundEffects.erase(iterator);
			break;
		}
		++iterator;
	}
}

/** \brief Loads a sound resource into a Music and returns it.
* Searches the ResourceManager's map of music for the specified music and returns a reference to it.
* If the music does not exist, loads it into memory and stores it in the map.
* \param filePath file path of the desired sound resource
*/
BG::Music* BG::ResourceManager::getMusic(const std::string &filePath)
{
	// Search the map of existing musics for the requested music
	auto result = mpMusic.find(filePath);

	if (result != mpMusic.end())
	{
		// The music exists and is already loaded into memory, return a reference to it
		return result->second;
	}

	// Attempt to load the sound resource into memory
	Music* music = loadMusic(filePath);

	// Insert the music into the musics map
	mpMusic.insert(std::pair<std::string, Mix_Music*>(filePath, music));

	return music;
}

/**
* \brief Free the memory associated with a music resource and remove it from the music map.
* Iterates through the music map, if a resource with the same file path is found, frees all associated memory and nullifies the pointer.
* \param filePath file path of the sound resource
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
			Logger::getInstance().log(Logger::INFO, "Freed resource \"" + iterator->first + "\"");
			iterator = mpMusic.erase(iterator);
			break;
		}
		++iterator;
	}
}

/**
* \brief Free the memory associated with a loaded resources and unload dependencies
*/
void BG::ResourceManager::free()
{
	// Obtain an instance of the Logger class
	Logger logger = Logger::getInstance();

	// Iterate through the map of textures
	std::map<std::string, SDL_Texture*>::iterator itTextures = mpTextures.begin();
	while (itTextures != mpTextures.end())
	{
		// Free the texture resource and erase the element from the map
		SDL_DestroyTexture(itTextures->second);
		logger.log(Logger::INFO, "Freed resource \"" + itTextures->first + "\"");
		itTextures = mpTextures.erase(itTextures);
	}

	// Unload the SDL_IMG libaries
	IMG_Quit();

	// Iterate through the map of sound effects
	std::map<std::string, Mix_Chunk*>::iterator itSoundEffects = mpSoundEffects.begin();
	while (itSoundEffects != mpSoundEffects.end())
	{
		// Free the sound effect resource and erase the element from the map
		Mix_FreeChunk(itSoundEffects->second);
		logger.log(Logger::INFO, "Freed resource \"" + itTextures->first + "\"");
		itSoundEffects = mpSoundEffects.erase(itSoundEffects);
	}

	// Iterate through the map of music
	std::map<std::string, Mix_Music*>::iterator itMusic = mpMusic.begin();
	while (itMusic != mpMusic.end())
	{
		// Free the music resource and erase the element from the map
		Mix_FreeMusic(itMusic->second);
		logger.log(Logger::INFO, "Freed resource \"" + itTextures->first + "\"");
		itMusic = mpMusic.erase(itMusic);
	}

	// Unload the Mix_Init libraries
	Mix_Quit();
}

/**
 * \brief Creates and returns a Texture of the specified size and colour.
 * \param size size of the texture in pixels
 * \param colour colour of the texture
 * \param window window the sprite will be rendered to
 */
BG::Texture* BG::ResourceManager::createTexture(const int& size, const Colour& colour, Window* window)
{
	// Create a texture of the specified size in streaming access mode so that we can edit its pixels
	SDL_Texture* texture = SDL_CreateTexture(window->getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, size, size);

	unsigned char* bytes = nullptr;
	int pitch = 0;

	// Obtain the texture's pixels	
	SDL_LockTexture(texture, nullptr, reinterpret_cast<void**>(&bytes), &pitch);

	// Fill the texture's pixels with the specified colour
	unsigned char rgba[4] = { colour.a, colour.r, colour.g, colour.b };
	for (int y = 0; y < size; ++y)
	{
		for (int x = 0; x < size; ++x)
		{
			memcpy(&bytes[(y * size + x) * sizeof(rgba)], rgba, sizeof(rgba));
		}
	}

	// Update the texture with the new pixels
	SDL_UnlockTexture(texture);

	return texture;
}

/**
 * \brief Load a texture from an image resource (BMP, GIF, JPEG, LBM, PCX, PNG, PNM, TGA, TIFF, WEBP, XCF, XPM, XV).
 * \param filePath file path of the image resource
 * \param window window the texture will be rendered to
 */
BG::Texture* BG::ResourceManager::loadTexture(const std::string &filePath, Window* window)
{
	SDL_Texture* texture = IMG_LoadTexture(window->getRenderer(), filePath.c_str());
	if(texture != nullptr)
	{
		Logger::getInstance().log(Logger::INFO, "Loaded \"" + filePath + "\"");
	}
	else
	{
		Logger::getInstance().log(Logger::ERROR, "Failed to load \"" + filePath + "\" (" + IMG_GetError() + ")");
	}
	return texture;
}

/**
 * \brief Load a sound effect from a sound resource (WAVE, MOD, MIDI, OGG, MP3).
 * \param filePath file path of the sound resource
 */
BG::SoundEffect* BG::ResourceManager::loadSoundEffect(const std::string &filePath)
{
	auto soundEffect = Mix_LoadWAV(filePath.c_str());
	if (soundEffect != nullptr)
	{
		Logger::getInstance().log(Logger::INFO, "Loaded \"" + filePath + "\"");
	}
	else
	{
		Logger::getInstance().log(Logger::ERROR, "Failed to load \"" + filePath + "\" (" + Mix_GetError() + ")");
	}
	return soundEffect;
}

/**
 * \brief Load music from a sound resource (WAVE, MOD, MIDI, OGG, MP3).
 * \param filePath file path of the sound resource
 */
BG::Music* BG::ResourceManager::loadMusic(const std::string &filePath)
{
	auto music = Mix_LoadMUS(filePath.c_str());
	if(music != nullptr)
	{
		Logger::getInstance().log(Logger::INFO, "Loaded \"" + filePath + "\"");
	}
	else
	{
		Logger::getInstance().log(Logger::ERROR, "Failed to load \"" + filePath + "\" (" + Mix_GetError() + ")");
	}
	return music;
}