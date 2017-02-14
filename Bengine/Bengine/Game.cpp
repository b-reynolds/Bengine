#include "Game.h"
#include "Logger.h"
#include <SDL_image.h>
#include "Colour.h"
#include "ResourceManager.h"

float Game::deltaTime = 0.0f;

bool Game::initialize()
{
	BG::Logger logger = BG::Logger::getInstance();

	// Initialize the video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		// Subsystem initialization failed, report error and exit.
		logger.log(BG::Logger::ERROR, std::string("Failed to initialize video subsystem (") + SDL_GetError() + ")");
		return false;
	}
	logger.log(BG::Logger::INFO, "Initialized video subsystem");

	// Initialize SDL_Image
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		logger.log(BG::Logger::ERROR, std::string("Failed to initialize SDL_Image (") + IMG_GetError() + ")");
		return false;
	}
	logger.log(BG::Logger::INFO, "Initialized SDL_Image");

	myWindow = new BG::Window("Test", BG::Vector2u(WIN_WIDTH, WIN_HEIGHT));

	auto resourceManager = BG::ResourceManager::getInstance();

	sprBackground = BG::Sprite(resourceManager->getTexture("Images/tile.bmp", myWindow), myWindow);
	sprLogo = BG::Sprite(resourceManager->getTexture("Images/Icon/bengine.fw.png", myWindow), myWindow);
	sprThing = BG::Sprite(resourceManager->getTexture("Images/thing.png", myWindow), myWindow);
	sprMouse = BG::Sprite(resourceManager->getTexture("Images/mouse.png", myWindow), myWindow);

	sprMouse.setSize(BG::Vector2i(67.83, 51.33));
	sprMouse.setOrigin(BG::Vector2f(sprMouse.getSize().x / 2, sprMouse.getSize().y / 2));

	objLogo = BG::GameObject(&sprLogo, BG::Vector2f(0, 0));


	auto logoSize = objLogo.getSprite()->getSize();
	objLogo.getTransform()->setPosition(BG::Vector2f(WIN_WIDTH / 2 - logoSize.x / 2, WIN_HEIGHT / 2 - logoSize.y / 2));
	objLogo.getSprite()->setOrigin(BG::Vector2f(logoSize.x / 2, logoSize.x / 2));

	objBackground = BG::GameObject(&sprBackground, BG::Vector2f(0, 0));	
	objThing = BG::GameObject(&sprThing, BG::Vector2f(25, 25));

	objMouse = BG::GameObject(&sprMouse, BG::Vector2f(0, 0));
	


	return true;
}

bool Game::run()
{
	if (!initialize())
	{
		exit();
		return false;
	}

	while (true)
	{
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		if (!update())
		{
			exit();
			return false;
		}

		draw();

		deltaTime = (NOW - LAST) * 1000 / SDL_GetPerformanceFrequency() * 0.001;
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

	const float SPEED = 1000.0f * deltaTime;

	if(keyboard->isKeyDown(SDLK_w))
	{
		objLogo.getTransform()->move(BG::Vector2f(0, -SPEED));
	}
	else if(keyboard->isKeyDown(SDLK_s))
	{
		objLogo.getTransform()->move(BG::Vector2f(0, SPEED));
	}

	if (keyboard->isKeyDown(SDLK_a))
	{
		objLogo.getTransform()->move(BG::Vector2f(-SPEED, 0));
	}
	else if (keyboard->isKeyDown(SDLK_d))
	{
		objLogo.getTransform()->move(BG::Vector2f(SPEED, 0));
	}

	objLogo.getTransform()->rotate(75 * deltaTime);

	myWindow->setTitle("Bengine | Delta Time: " + std::to_string(deltaTime));

	if(myTimer.hasExpired())
	{
		objMouse.getTransform()->rotate(90);
		myTimer.reset();
	}

	mouse->swapStates();
	keyboard->swapStates();

	return true;
}

void Game::draw()
{
	// Clear the renderer
	myWindow->clear();

	auto tileSize = objBackground.getSprite()->getSize();

	auto tiles = BG::Vector2i(WIN_WIDTH / tileSize.x, WIN_HEIGHT / tileSize.y);

	for (int x = 0; x < tiles.x; ++x)
	{
		for (int y = 0; y < tiles.y; ++y)  
		{
			objBackground.getTransform()->setPosition(BG::Vector2f(x * tileSize.x, y * tileSize.y));
			myWindow->draw(objBackground);
		}
	}

	for (int j = 1; j <= 3; ++j)
	{
		for (int i = 0; i <= 255; ++i)
		{
			objThing.getTransform()->setPosition(BG::Vector2f(32 + i, j * 64));
			myWindow->draw(objThing, BG::Colour(j == 1 ? i : 0, j == 2 ? i : 0, j == 3 ? i : 0));
		}
	}


	myWindow->draw(objLogo);
	myWindow->draw(objLogo.getBounds(), BG::Colour(255, 255, 0));

	objMouse.getTransform()->setPosition(BG::Vector2f(mouse->getPosition().x, mouse->getPosition().y));
	myWindow->draw(objMouse);

	myWindow->draw(objMouse.getBounds(), BG::Colour(0, 255, 0));



	// Update the screen
	myWindow->display();
}

void Game::exit() const
{
	if (myWindow != nullptr)
	{
		myWindow->destroy();
	}
	BG::Logger logger = BG::Logger::getInstance();
	logger.log(BG::Logger::INFO, "Unloading Mix_Init");
	Mix_Quit();
	logger.log(BG::Logger::INFO, "Unloading IMG_Init");
	IMG_Quit();
	logger.log(BG::Logger::INFO, "Cleaning up SDL subsystems");
	SDL_Quit();
	logger.log(BG::Logger::INFO, "Exiting application");
}

Game::Game()
{
	keyboard = BG::Keyboard::getInstance();
	mouse = BG::Mouse::getInstance();

	myWindow = nullptr;

	NOW = SDL_GetPerformanceCounter();
	LAST = 0;
	deltaTime = 0.0f;
}

Game::~Game()
{
}
