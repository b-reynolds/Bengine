#pragma once
#include <SDL_render.h>
#include <map>

class ResourceManager
{

private:

	std::map<std::string, SDL_Texture*> textureMap;

	static ResourceManager *instance;
	ResourceManager();

	static SDL_Texture* createTexture(const int &size, const unsigned char &r, const unsigned char &g, const unsigned char &b, const unsigned char &a, SDL_Renderer *renderer);
	static SDL_Texture* loadTexture(const std::string &filePath, SDL_Renderer *renderer);

public:

	static ResourceManager* getInstance();
	ResourceManager::~ResourceManager();

	SDL_Texture* getTexture(const std::string &filePath, SDL_Renderer *renderer);

};

