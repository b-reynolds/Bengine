#include "resource_manager.h"
#include "Logger.h"
#include "window.h"
#include "Bengine.h"
#include "colour.h"
#include <SDL_image.h>
#include <iterator>

// Initialize static members
BG::ResourceManager* BG::ResourceManager::instance_ = nullptr;

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
BG::ResourceManager* BG::ResourceManager::instance()
{
	if(instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
	return instance_;
}

/**
 * \brief Loads a script resource into a string and returns it
 * \param file_path path of desired script resource
 */
std::string* BG::ResourceManager::script(const std::string& file_path)
{
	auto result = scripts_.find(file_path);

	if(result != scripts_.end())
	{
		return result->second;
	}

	std::string* script = load_script(file_path);

	scripts_.insert(std::pair<std::string, std::string*>(file_path, script));

	return script;
}

/** \brief Loads an image resource into a Texture and returns it.
* Searches the ResourceManager's map of textures for the specified texture and returns a reference to it.
* If the texture does not exist, loads it into memory and stores it in the map.
* If the the texture fails to load, creates a placeholder texture in its place.
* \param file_path file path of the desired image resource
* \param window window the texture will be rendered to
*/
BG::Texture* BG::ResourceManager::texture(const std::string& file_path, Window* window)
{
	// Search the map of existing textures for the requested texture
	auto result = textures_.find(file_path);

	if (result != textures_.end())
	{
		// The texture exists and is already loaded into memory, return a reference to it
		return result->second;
	}

	// Attempt to load the image resource into memory
	Texture* texture = load_texture(file_path, window);

	if (texture == nullptr)
	{
		// The texture failed to load, create a placeholder texture
		texture = create_texture(kTextureSizeDefault, kTextureColourDefault, window);
	}

	// Insert the texture into the textures map
	textures_.insert(std::pair<std::string, Texture*>(file_path, texture));

	return texture;
}

/**
* \brief Free the memory associated with an image resource and remove it from the textures map.
* Iterates through the textures map, if a resource with the same file path is found, frees all associated memory and nullifies the pointer.
* \param file_path file path of the image resource
*/
void BG::ResourceManager::free_texture(const std::string &file_path)
{
	std::map<std::string, SDL_Texture*>::iterator iterator = textures_.begin();
	while (iterator != textures_.end())
	{
		if (iterator->first == file_path)
		{
			Texture* texture = iterator->second;
			SDL_DestroyTexture(texture);
			texture = nullptr;
			Logger::instance().log(Logger::kInfo, "Freed resource \"" + iterator->first + "\"");
			iterator = textures_.erase(iterator);
			break;
		}
		++iterator;
	}
}

/** \brief Loads a sound resource into a SoundEffect and returns it.
* Searches the ResourceManager's map of sound effects for the specified sound effect and returns a reference to it.
* If the sound effect does not exist, loads it into memory and stores it in the map.
* \param file_path file path of the desired sound resource
*/
BG::SoundEffect* BG::ResourceManager::sound_effect(const std::string &file_path)
{
	// Search the map of existing sound effects for the requested sound effect
	auto result = sound_effects_.find(file_path);

	if (result != sound_effects_.end())
	{
		// The sound effect exists and is already loaded into memory, return a reference to it
		return result->second;
	}

	// Attempt to load the sound resource into memory
	SoundEffect* soundEffect = load_sound_effect(file_path);

	// Insert the sound effect into the sound effects map
	sound_effects_.insert(std::pair<std::string, Mix_Chunk*>(file_path, soundEffect));

	return soundEffect;
}

/**
* \brief Free the memory associated with a sound effect resource and remove it from the sound effects map.
* Iterates through the sound effects map, if a resource with the same file path is found, frees all associated memory and nullifies the pointer.
* \param file_path file path of the sound resource
*/
void BG::ResourceManager::free_sound_effect(const std::string &file_path)
{
	std::map<std::string, Mix_Chunk*>::iterator itSoundEffects = sound_effects_.begin();
	while (itSoundEffects != sound_effects_.end())
	{
		if (itSoundEffects->first == file_path)
		{
			SoundEffect* soundEffect = itSoundEffects->second;
			Mix_FreeChunk(soundEffect);
			soundEffect = nullptr;
			Logger::instance().log(Logger::kInfo, "Freed resource \"" + itSoundEffects->first + "\"");
			itSoundEffects = sound_effects_.erase(itSoundEffects);
		}
		else
		{
			++itSoundEffects;
		}
	}
}

/** \brief Loads a sound resource into a Music and returns it.
* Searches the ResourceManager's map of music for the specified music and returns a reference to it.
* If the music does not exist, loads it into memory and stores it in the map.
* \param file_path file path of the desired sound resource
*/
BG::Music* BG::ResourceManager::music(const std::string &file_path)
{
	// Search the map of existing musics for the requested music
	auto result = music_.find(file_path);

	if (result != music_.end())
	{
		// The music exists and is already loaded into memory, return a reference to it
		return result->second;
	}

	// Attempt to load the sound resource into memory
	Music* music = load_music(file_path);

	// Insert the music into the musics map
	music_.insert(std::pair<std::string, Mix_Music*>(file_path, music));

	return music;
}

/**
* \brief Free the memory associated with a music resource and remove it from the music map.
* Iterates through the music map, if a resource with the same file path is found, frees all associated memory and nullifies the pointer.
* \param file_path file path of the sound resource
*/
void BG::ResourceManager::free_music(const std::string &file_path)
{
	std::map<std::string, Music*>::iterator itMusic = music_.begin();
	while (itMusic != music_.end())
	{
		if (itMusic->first == file_path)
		{
			Music* music = itMusic->second;
			Mix_FreeMusic(music);
			music = nullptr;
			Logger::instance().log(Logger::kInfo, "Freed resource \"" + itMusic->first + "\"");
			itMusic = music_.erase(itMusic);
		}
		else
		{
			++itMusic;
		}
	}
}

/** \brief Loads a font resource into a Font and returns it.
* Searches the ResourceManager's map of fonts for the specified font and returns a reference to it.
* If the font does not exist, loads it into memory and stores it in the map.
* \param file_path file path of the desired font resource (TTF)
* \param size desired font size
*/
BG::Font* BG::ResourceManager::font(const std::string& file_path, const int& size)
{
	// Search the map of existing fonts for the requested font
	auto result = fonts_.find(file_path);

	if (result != fonts_.end() && result->second.second == size)
	{
		// The font already exists is already loaded into memory, return a reference to it
		return result->second.first;
	}

	// Attempt to load the font resource into memory
	Font* font = load_font(file_path, size);

	// Insert the font into the fonts map
	fonts_.emplace(std::make_pair(file_path, std::make_pair(font, size)));

	return font;
}

/**
* \brief Free the memory associated with a font resource and remove it from the font map.
* Iterates through the font map, if a resource with the same file path is found, frees all associated memory and nullifies the pointer.
* \param file_path file path of the font resource
*/
void BG::ResourceManager::free_font(const std::string& file_path)
{
	std::map<std::string, std::pair<Font*, int>>::iterator itFonts = fonts_.begin();
	while (itFonts != fonts_.end())
	{
		if (itFonts->first == file_path)
		{
			Font* font = itFonts->second.first;
			TTF_CloseFont(font);
			font = nullptr;
			Logger::instance().log(Logger::kInfo, "Freed resource \"" + itFonts->first + "\"");
			itFonts = fonts_.erase(itFonts);
		}
		else
		{
			++itFonts;
		}
	}
}

/**
* \brief Free the memory associated with a loaded resources and unload dependencies
*/
void BG::ResourceManager::free()
{
	// Obtain an instance of the Logger class
	Logger logger = Logger::instance();

	// Iterate through the map of textures
	std::map<std::string, SDL_Texture*>::iterator itTextures = textures_.begin();
	while (itTextures != textures_.end())
	{
		// Free the texture resource and erase the element from the map
		SDL_DestroyTexture(itTextures->second);
		logger.log(Logger::kInfo, "Freed resource \"" + itTextures->first + "\"");
		itTextures = textures_.erase(itTextures);
	}

	// Iterate through the map of sound effects
	std::map<std::string, Mix_Chunk*>::iterator itSoundEffects = sound_effects_.begin();
	while (itSoundEffects != sound_effects_.end())
	{
		// Free the sound effect resource and erase the element from the map
		Mix_FreeChunk(itSoundEffects->second);
		logger.log(Logger::kInfo, "Freed resource \"" + itTextures->first + "\"");
		itSoundEffects = sound_effects_.erase(itSoundEffects);
	}

	// Iterate through the map of music
	std::map<std::string, Mix_Music*>::iterator itMusic = music_.begin();
	while (itMusic != music_.end())
	{
		// Free the music resource and erase the element from the map
		Mix_FreeMusic(itMusic->second);
		logger.log(Logger::kInfo, "Freed resource \"" + itTextures->first + "\"");
		itMusic = music_.erase(itMusic);
	}

	// Iterate through the map of fonts
	std::map<std::string, std::pair<Font*, int>>::iterator itFonts = fonts_.begin();
	while(itFonts != fonts_.end())
	{
		// Free the font resource and erase the element from the map
		TTF_CloseFont(itFonts->second.first);
		logger.log(Logger::kInfo, "Freed resource \"" + itFonts->first + "\"");
		itFonts = fonts_.erase(itFonts);
	}
}

/**
 * \brief Loads a script from a text file
 * \param file_path path of script resource
 */
std::string* BG::ResourceManager::load_script(const std::string& file_path) const
{
	std::ifstream input_stream;
	input_stream.open(file_path);

	if(!input_stream.is_open())
	{
		return nullptr;
	}

	std::string* file_contents = new std::string{ std::istreambuf_iterator<char>(input_stream), std::istreambuf_iterator<char>() };

	return file_contents;
}

/**
 * \brief Creates and returns a Texture of the specified size and colour.
 * \param size size of the texture in pixels
 * \param colour colour of the texture
 * \param window window the sprite will be rendered to
 */
BG::Texture* BG::ResourceManager::create_texture(const int& size, const Colour& colour, Window* window) const
{
	// Create a texture of the specified size in streaming access mode so that we can edit its pixels
	Texture* texture = SDL_CreateTexture(window->renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, size, size);

	unsigned char* bytes = nullptr;
	int pitch = 0;

	// Obtain the texture's pixels	
	SDL_LockTexture(texture, nullptr, reinterpret_cast<void**>(&bytes), &pitch);

	// Fill the texture's pixels with the specified colour
	unsigned char rgba[4] = { colour.a_, colour.r_, colour.g_, colour.b_ };
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
 * \brief Loads a texture from an image resource (BMP, GIF, JPEG, LBM, PCX, PNG, PNM, TGA, TIFF, WEBP, XCF, XPM, XV).
 * \param file_path file path of the image resource
 * \param window window the texture will be rendered to
 */
BG::Texture* BG::ResourceManager::load_texture(const std::string &file_path, Window* window) const
{
	Texture* texture = IMG_LoadTexture(window->renderer(), file_path.c_str());
	if(texture != nullptr)
	{
		Logger::instance().log(Logger::kInfo, "Loaded \"" + file_path + "\"");
	}
	else
	{
		Logger::instance().log(Logger::kError, "Failed to load \"" + file_path + "\" (" + IMG_GetError() + ")");
	}
	return texture;
}

/**
 * \brief Loads a sound effect from a sound resource (WAVE, MOD, MIDI, OGG, MP3).
 * \param file_path file path of the sound resource
 */
BG::SoundEffect* BG::ResourceManager::load_sound_effect(const std::string &file_path) const
{
	SoundEffect* soundEffect = Mix_LoadWAV(file_path.c_str());
	if (soundEffect != nullptr)
	{
		Logger::instance().log(Logger::kInfo, "Loaded \"" + file_path + "\"");
	}
	else
	{
		Logger::instance().log(Logger::kError, "Failed to load \"" + file_path + "\" (" + Mix_GetError() + ")");
	}
	return soundEffect;
}

/**
 * \brief Loads music from a sound resource (WAVE, MOD, MIDI, OGG, MP3).
 * \param file_path file path of the sound resource
 */
BG::Music* BG::ResourceManager::load_music(const std::string &file_path) const
{
	Music* music = Mix_LoadMUS(file_path.c_str());
	if(music != nullptr)
	{
		Logger::instance().log(Logger::kInfo, "Loaded \"" + file_path + "\"");
	}
	else
	{
		Logger::instance().log(Logger::kError, "Failed to load \"" + file_path + "\" (" + Mix_GetError() + ")");
	}
	return music;
}

/*
 * \brief Loads a font from a TTF file
 * \param filePath file path of font resource
 * \param size desired font size
 */
BG::Font* BG::ResourceManager::load_font(const std::string& file_path, const int& size) const
{
	Font* font = TTF_OpenFont(file_path.c_str(), size);
	if(font != nullptr)
	{
		Logger::instance().log(Logger::kInfo, "Loaded \"" + file_path + "\"");
	}
	else
	{
		Logger::instance().log(Logger::kError, "Failed to load \"" + file_path + "\" (" + TTF_GetError() + ")");
	}
	return font;
}
