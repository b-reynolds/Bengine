#pragma once
#include "BengineTypedefs.h"
#include "Colour.h"
#include <map>

namespace BG
{
	// Forward Declaration
	class Window;

	/*
	 * \brief Resource Manager Class
	 * Handles the loading and distribution of image and sound resources.
	 * Insures only one instance of any particular resource is loaded at any one time.
	 */
	class ResourceManager
	{

	public:

		/* Returns a pointer to the singleton instance of the Resource Manager class */
		static ResourceManager* getInstance();

		/* Frees dynamically allocated memory and unloads dependencies */
		ResourceManager::~ResourceManager();

		/* Loads an image resource into a Texture and returns it */
		Texture* getTexture(const std::string &filePath, Window* window);

		/* Frees the memory associated with an image resource and removes it from the textures map */
		void freeTexture(const std::string &filePath);

		/* Loads a sound resource into a SoundEffect and returns it */
		SoundEffect* getSoundEffect(const std::string &filePath);

		/* Frees the memory associated with a sound effect resource and removes it from the sound effects map */
		void freeSoundEffect(const std::string &filePath);

		/* Loads a sound resource into a Music and returns it */
		Music* getMusic(const std::string &filePath);

		/* Frees the memory associated with a music resource and removes it from the music map */
		void freeMusic(const std::string &filePath);

		/* Loads a font resource into a Font and returns it */
		Font* getFont(const std::string &filePath, const int &size);

		/* Frees the memory associated with a font resource and removes it from the music map */
		void freeFont(const std::string &filePath);

		/* Free all memory associated with loaded resources and unload all dependencies */
		void free();

	private:

		/* Default colour for placeholder textures */
		const Colour TEXTURE_COLOUR_DEFAULT = CLR_PINK;

		/* Default size of placeholder textures */
		const int TEXTURE_SIZE_DEFAULT = 32;

		/* Map that stores Texture resources */
		std::map<std::string, Texture*> mpTextures;

		/* Map that stores SoundEffect resources */
		std::map<std::string, SoundEffect*> mpSoundEffects;

		/* Map that stores Music resources */
		std::map <std::string, Music*> mpMusic;

		/* Map that stores Font resources */
		std::map<std::string, std::pair<Font*, int>> mpFonts;

		/* The singleton instance of ResourceManager */
		static ResourceManager* instance;

		/* Private default constructor */
		ResourceManager();

		/* Creates and returns a Texture of the specified size and colour */
		Texture* createTexture(const int &size, const Colour &colour, Window *window) const;	

		/* Loads an image resource into a Texture and returns it */
		Texture* loadTexture(const std::string &filePath, Window* window) const;

		/* Loads a sound resource into a SoundEffect and returns it */
		SoundEffect* loadSoundEffect(const std::string &filePath) const;
		
		/* Loads a sound resource into a Music and returns it */
		Music* loadMusic(const std::string &filePath) const;

		/* Loads a font resource from a TTF file into a Font and returns it */
		Font* loadFont(const std::string &filePath, const int &size) const;

	};

}