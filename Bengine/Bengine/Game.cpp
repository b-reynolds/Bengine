#include "Game.h"
#include "Bengine.h"

bool Game::run(BG::Window* window)
{
	this->window = window;

	// If the game fails to initialize then discontinue
	if(!initialized && !((initialized = initialize())))
	{
		return false;
	}

	if (!update())
	{
		exit();
		return false;
	}

	draw();

	return true;
}

bool Game::initialize()
{
	BG::Texture* txtrLogo = BG::ResourceManager::getInstance()->getTexture("Images/Icon/bengine.fw.png", window);
	sprLogo = BG::Sprite(txtrLogo, window);

	BG::Vector2f logoSize = sprLogo.getSize();
	BG::Vector2i windowSize = window->getSize();

	objLogo = BG::GameObject(&sprLogo, BG::Vector2f(windowSize.x / 2 - logoSize.x / 2,
		windowSize.y / 2 - logoSize.y / 2));

	myOtherText = BG::Text(BG::ResourceManager::getInstance()->getFont("Fonts/Horta.ttf", 64), "Hey", window);

	myText = BG::Text(BG::ResourceManager::getInstance()->getFont("Fonts/Horta.ttf", 32), "Hi", window);


	myText.setColour(BG::CLR_WHITE);
	myText.setText("Hello World");
	myText.getTransform().setPosition(BG::Vector2f(250, 250));

	myOtherText.setColour(BG::CLR_WHITE);
	myOtherText.getTransform().setPosition(BG::Vector2f(450, 250));

	return true;
}

bool Game::update()
{
	objLogo.getSprite()->setOrigin(objLogo.getSprite()->getSize() / 2);
	objLogo.getTransform()->rotate(1);

	myText.getTransform().rotate(1);


	BG::Vector2f logoPosition = objLogo.getTransform()->getPosition();
	auto keyboard = BG::Keyboard::getInstance();
	
	if(keyboard->isKeyDown(SDLK_w))
	{
		logoPosition.y -= SPEED * BG::Bengine::deltaTime;
	}
	else if(keyboard->isKeyDown(SDLK_s))
	{
		logoPosition.y += SPEED * BG::Bengine::deltaTime;
	}

	if(keyboard->isKeyDown(SDLK_a))
	{
		logoPosition.x -= SPEED * BG::Bengine::deltaTime;
	}
	else if(keyboard->isKeyDown(SDLK_d))
	{
		logoPosition.x += SPEED * BG::Bengine::deltaTime;
		BG::ResourceManager::getInstance()->freeTexture("Images/Icon/bengine.fw.png");
	}

	objLogo.getTransform()->setPosition(logoPosition);

	return true;
}

void Game::draw()
{
	// Clear the renderer
	window->clear();

	window->draw(objLogo);

	window->draw(myText);
	window->draw(myOtherText);

	window->draw(myOtherText.getBounds(), BG::CLR_RED);
	window->draw(myText.getBounds(), BG::CLR_RED);
	window->draw(objLogo.getBounds(), BG::CLR_RED);

	// Update the screen
	window->display();
}

void Game::exit()
{

}