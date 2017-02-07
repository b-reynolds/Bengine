#include "Game.h"
#include "Logger.h"
#include <SDL_image.h>
#include "ResourceManager.h"
#include "Renderer.h"

bool Game::initialize()
{
	BG::Logger* logger = BG::Logger::getInstance();

	// Initialize the video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		// Subsystem initialization failed, report error and exit.
		logger->log(BG::Logger::ERROR, std::string("Failed to initialize video subsystem (") + SDL_GetError() + ")");
		SDL_Quit();
		return false;
	}
	logger->log(BG::Logger::INFO, "Initialized video subsystem");

	// Initialize SDL_Image
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		logger->log(BG::Logger::ERROR, std::string("Failed to initialize SDL_Image (") + IMG_GetError() + ")");
		SDL_Quit();
		return false;
	}
	logger->log(BG::Logger::INFO, "Initialized SDL_Image");

	// Create the window used for rendering
	window = SDL_CreateWindow(WIN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_OPENGL);

	if (window == nullptr)
	{
		// Window creation failed, report error, clean up and exit.
		logger->log(BG::Logger::ERROR, std::string("Failed to create window (") + SDL_GetError() + ")");
		SDL_Quit();
		return false;
	}
	logger->log(BG::Logger::INFO, "Created window");

	// Create a renderer with hardware acceleration and vsync enabled
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr)
	{
		// Render creation failed, report error, clean up and exit.
		logger->log(BG::Logger::ERROR, std::string("Failed to create renderer") + SDL_GetError() + ")");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}
	logger->log(BG::Logger::INFO, "Created renderer");

	auto resourceManager = BG::ResourceManager::getInstance();

	txtrBackground = resourceManager->getTexture("Images/tile.bmp", renderer);
	txtrLogo = resourceManager->getTexture("Images/Icon/bengine.fw.png", renderer);

	return true;
}

bool Game::run()
{
	if (!initialize()) return false;
	while (true)
	{
		if (!update())
		{
			BG::Logger::getInstance()->log(BG::Logger::INFO, "Exiting application");
			SDL_DestroyTexture(txtrBackground);
			SDL_DestroyTexture(txtrLogo);
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			return false;
		}
		draw();
	}
}

bool Game::update()
{
	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				return false;
			case SDL_MOUSEBUTTONDOWN:
				mouse->setMouseState(event.button.button, true);
				break;
			case SDL_MOUSEBUTTONUP:
				mouse->setMouseState(event.button.button, false);
				break;
			case SDL_KEYDOWN:
				keyboard->setKeyState(event.key.keysym.sym, true);
				break;
			case SDL_KEYUP:
				keyboard->setKeyState(event.key.keysym.sym, false);
				break;
			default: break;
		}
	}

	mouse->swapStates();
	keyboard->swapStates();

	return true;
}

void Game::draw()
{
	// Clear the renderer
	SDL_RenderClear(renderer);

	auto tileSize = BG::Vector2i();
	SDL_QueryTexture(txtrBackground, nullptr, nullptr, &tileSize.x, &tileSize.y);

	auto tiles = BG::Vector2i(WIN_WIDTH / tileSize.x, WIN_HEIGHT / tileSize.y);

	for (int x = 0; x < tiles.x; ++x)
	{
		for (int y = 0; y < tiles.y; ++y)  
		{
			BG::Renderer::renderTexture(txtrBackground, renderer, x * tileSize.x, y * tileSize.y);
		}
	}

	auto logoSize = BG::Vector2i();
	
	SDL_QueryTexture(txtrLogo, nullptr, nullptr, &logoSize.x, &logoSize.y);

	BG::Renderer::renderTexture(txtrLogo, renderer, WIN_WIDTH / 2 - logoSize.x / 2, WIN_HEIGHT / 2 - logoSize.y / 2, logoSize.x, logoSize.y );

	// Update the screen
	SDL_RenderPresent(renderer);
}

Game::Game()
{
	mouse = BG::Mouse::getInstance();
	keyboard = BG::Keyboard::getInstance();
	renderer = nullptr;
	window = nullptr;
	txtrBackground = nullptr;
	txtrLogo = nullptr;
}

Game::~Game()
{
}
