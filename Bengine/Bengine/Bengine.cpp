#include "Bengine.h"
#include "Logger.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Game.h"

// Initialize static members
float BG::Bengine::deltaTime = 0.0f;

/*
 * \brief Initializes Bengine and all of it's dependencies
 */
bool BG::Bengine::initialize()
{
	mouse = Mouse::getInstance();
	keyboard = Keyboard::getInstance();

	auto logger = Logger::getInstance();

	// Initialize the SDL video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		logger.log(BG::Logger::ERROR, std::string("Failed to initialize video subsystem (") + SDL_GetError() + ")");
		SDL_Quit();
		return false;
	}
	logger.log(BG::Logger::INFO, "Initialized video subsystem");

	// Initialize SDL_Image
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		logger.log(BG::Logger::ERROR, std::string("Failed to initialize SDL_Image (") + IMG_GetError() + ")");
		SDL_Quit();
		IMG_Quit();
		return false;
	}
	logger.log(BG::Logger::INFO, "Initialized SDL_Image");

	// Initialize Mix_Init with support for the OGG sound resources
	int flags = MIX_INIT_OGG;
	if(Mix_Init(flags != flags))
	{
		logger.log(Logger::ERROR, std::string("Failed to initialize Mix_Init (") + Mix_GetError() + ")");
		SDL_Quit();
		IMG_Quit();
		Mix_Quit();
		return false;
	}
	logger.log(Logger::INFO, "Initialized Mix_Init");

	window = new Window(WIN_TITLE, Vector2u(WIN_WIDTH, WIN_HEIGHT));

	if(!window->isOpen())
	{
		return false;
	}

	return true;
}

/*
 * \brief Cleans up and Exits Bengine
 */
void BG::Bengine::exit()
{
	auto logger = Logger::getInstance();

	window->destroy();

	logger.log(Logger::INFO, "Unloading Mix_Init");
	Mix_Quit();
	logger.log(Logger::INFO, "Unloading IMG_Init");
	IMG_Quit();
	logger.log(Logger::INFO, "Cleaning up SDL subsystems");
	SDL_Quit();
	logger.log(Logger::INFO, "Exiting application");
}

/*
 * \brief Initializing Contructor
 */
BG::Bengine::Bengine()
{
	mouse = nullptr;
	keyboard = nullptr;
	window = nullptr;
	current = 0;
	last = 0;
}

/*
 * \brief Run the game engine
 * Processes the event loop and calculates delta time.
 */
bool BG::Bengine::run()
{
	// If the engine fails to initialize then discontinue
	if(!initialize())
	{
		return false;
	}

	// Create an instance of the Game
	Game game = Game();

	while (true)
	{
		// Swap the high resolution counter buffers
		last = current;
		current = SDL_GetPerformanceCounter();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					game.exit();
					exit();
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

		if(!game.run(window))
		{
			exit();
			return false;
		}

		// Swap the mouse and keyboard buffers
		mouse->swapStates();
		keyboard->swapStates();

		// Calculate delta time
		deltaTime = (current - last) * 1000 / SDL_GetPerformanceFrequency() * 0.001;
	}

	return false;
}
