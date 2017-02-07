#pragma once
#include <SDL_render.h>
#include <SDL_mixer.h>
#include <map>

namespace BG
{
	class ResourceManager
	{

	private:

		std::map<std::string, SDL_Texture*> mpTextures;
		std::map<std::string, Mix_Chunk*> mpSoundEffects;
		std::map <std::string, Mix_Music*> mpMusic;

		static ResourceManager *instance;
		ResourceManager();

		static SDL_Texture* createTexture(const int &size, const unsigned char &r, const unsigned char &g, const unsigned char &b, const unsigned char &a, SDL_Renderer *renderer);
		static SDL_Texture* loadTexture(const std::string &filePath, SDL_Renderer *renderer);

		static Mix_Chunk* loadSoundEffect(const std::string &filePath);
		static Mix_Music* loadMusic(const std::string &filePath);

	public:

		static ResourceManager* getInstance();
		ResourceManager::~ResourceManager();

		SDL_Texture* getTexture(const std::string &filePath, SDL_Renderer *renderer);
		Mix_Chunk* getSoundEffect(const std::string &filePath);
		Mix_Music* getMusic(const std::string &filePath);

		void freeTexture(const std::string &filePath);
		void freeSoundEffect(const std::string &filePath);
		void freeMusic(const std::string &filePath);

	};
}

