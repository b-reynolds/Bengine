#include "bengine.h"
#include "Logger.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "game.h"

// Initialize static members
float BG::Bengine::delta_time_ = 0.0f;

/*
 * \brief Initializes Bengine and all of it's dependencies
 */
bool BG::Bengine::initialize()
{
	mouse_ = Mouse::instance();
	keyboard_ = Keyboard::instance();

	auto logger = Logger::instance();

	// Initialize the SDL video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		logger.log(BG::Logger::kError, std::string("Failed to initialize video subsystem (") + SDL_GetError() + ")");
		SDL_Quit();
		return false;
	}
	logger.log(BG::Logger::kInfo, "Initialized video subsystem");

	// Initialize SDL_Image
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		logger.log(BG::Logger::kError, std::string("Failed to initialize SDL_Image (") + IMG_GetError() + ")");
		SDL_Quit();
		IMG_Quit();
		return false;
	}
	logger.log(BG::Logger::kInfo, "Initialized SDL_Image");

	// Initialize Mix_Init with support for the OGG sound resources
	int flags = MIX_INIT_OGG;
	if(Mix_Init(flags != flags))
	{
		logger.log(Logger::kError, std::string("Failed to initialize SDL_Mix (") + Mix_GetError() + ")");
		SDL_Quit();
		IMG_Quit();
		Mix_Quit();
		return false;
	}
	logger.log(Logger::kInfo, "Initialized SDL_Mix");

	// Initialize open audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == 1)
	{
		logger.log(Logger::kError, std::string("Failed to initialize Open Audio (") + Mix_GetError() + ")");
		return false;
	}

	if (TTF_Init() != 0)
	{
		logger.log(Logger::kError, std::string("Failed to initialize SDL_TTF (") + TTF_GetError() + ")");
		SDL_Quit();
		IMG_Quit();
		Mix_Quit();
		return false;
	}
	logger.log(Logger::kInfo, "Initialized SDL_TTF");


	window_ = new Window(kWinTitle, Vector2u(kWinWidth, kWinHeight));

	if(!window_->open())
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
	auto logger = Logger::instance();

	window_->destroy();

	logger.log(Logger::kInfo, "Unloading Mix_Init");
	Mix_Quit();
	logger.log(Logger::kInfo, "Unloading IMG_Init");
	IMG_Quit();
	logger.log(Logger::kInfo, "Cleaning up SDL subsystems");
	SDL_Quit();
	logger.log(Logger::kInfo, "Exiting application");
}

float BG::Bengine::delta_time()
{
	return delta_time_;
}

/*
 * \brief Initializing Contructor
 */
BG::Bengine::Bengine()
{
	mouse_ = nullptr;
	keyboard_ = nullptr;
	window_ = nullptr;
	current_ = 0;
	last_ = 0;
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
		last_ = current_;
		current_ = SDL_GetPerformanceCounter();

		while (SDL_PollEvent(&event_))
		{
			switch (event_.type)
			{
				case SDL_QUIT:
					game.exit();
					exit();
					return false;
				case SDL_MOUSEBUTTONDOWN:
					mouse_->set_mouse_state(event_.button.button, true);
					break;
				case SDL_MOUSEBUTTONUP:
					mouse_->set_mouse_state(event_.button.button, false);
					break;
				case SDL_KEYDOWN:
					keyboard_->set_key_state(event_.key.keysym.sym, true);
					break;
				case SDL_KEYUP:
					keyboard_->set_key_state(event_.key.keysym.sym, false);
					break;
			default: break;
			}
		}

		if(!game.run(window_))
		{
			exit();
			return false;
		}

		// Swap the mouse and keyboard buffers
		mouse_->swap_states();
		keyboard_->swap_states();

		// Calculate delta time
		delta_time_ = (current_ - last_) * 1000 / SDL_GetPerformanceFrequency() * 0.001;
	}

	return false;
}
