#pragma once
#include "bengine_typedefs.h"
#include "colour.h"
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
		static ResourceManager* instance();

		/* Frees dynamically allocated memory and unloads dependencies */
		ResourceManager::~ResourceManager();

		/* Loads an image resource into a Texture and returns it */
		Texture* texture(const std::string &file_path, Window* window);

		/* Frees the memory associated with an image resource and removes it from the textures map */
		void free_texture(const std::string &file_path);

		/* Loads a sound resource into a SoundEffect and returns it */
		SoundEffect* sound_effect(const std::string &file_path);

		/* Frees the memory associated with a sound effect resource and removes it from the sound effects map */
		void free_sound_effect(const std::string &file_path);

		/* Loads a sound resource into a Music and returns it */
		Music* music(const std::string &file_path);

		/* Frees the memory associated with a music resource and removes it from the music map */
		void free_music(const std::string &file_path);

		/* Loads a font resource into a Font and returns it */
		Font* font(const std::string &file_path, const int &size);

		/* Frees the memory associated with a font resource and removes it from the music map */
		void free_font(const std::string &file_path);

		/* Free all memory associated with loaded resources and unload all dependencies */
		void free();

	private:

		/* Default colour for placeholder textures */
		const Colour kTextureColourDefault = kClrPink;

		/* Default size of placeholder textures */
		const int kTextureSizeDefault = 32;

		/* Map that stores Texture resources */
		std::map<std::string, Texture*> mpTextures_;

		/* Map that stores SoundEffect resources */
		std::map<std::string, SoundEffect*> mpSoundEffects_;

		/* Map that stores Music resources */
		std::map <std::string, Music*> mpMusic_;

		/* Map that stores Font resources */
		std::map<std::string, std::pair<Font*, int>> mpFonts_;

		/* The singleton instance of ResourceManager */
		static ResourceManager* instance_;

		/* Private default constructor */
		ResourceManager();

		/* Creates and returns a Texture of the specified size and colour */
		Texture* create_texture(const int &size, const Colour &colour, Window *window) const;	

		/* Loads an image resource into a Texture and returns it */
		Texture* load_texture(const std::string &file_path, Window* window) const;

		/* Loads a sound resource into a SoundEffect and returns it */
		SoundEffect* load_sound_effect(const std::string &file_path) const;
		
		/* Loads a sound resource into a Music and returns it */
		Music* load_music(const std::string &file_path) const;

		/* Loads a font resource from a TTF file into a Font and returns it */
		Font* load_font(const std::string &file_path, const int &size) const;

	};

}