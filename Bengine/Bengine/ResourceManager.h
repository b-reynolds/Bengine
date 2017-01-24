#pragma once
#include <SDL_render.h>
#include <string>

class ResourceManager
{

private:

	static ResourceManager *instance;
	ResourceManager();

public:

	static ResourceManager* getInstance();
	ResourceManager::~ResourceManager();

	SDL_Texture* loadTexture(const std::string &filePath, SDL_Renderer *renderer);

};

