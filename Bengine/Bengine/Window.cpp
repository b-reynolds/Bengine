#include "Window.h"
#include "Logger.h"
#include "GameObject.h"
#include "Colour.h"

/*
 * \brief Creates and initializes a Window with the specified title and of the specified size
 * \param title Window title
 * \param size Window size
 */
BG::Window::Window(const std::string& title, const Vector2u& size)
{
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.x, size.y, SDL_WINDOW_OPENGL);

	auto logger = Logger::getInstance();

	if(window == nullptr)
	{
		// Window creation failed, report error, clean up and exit.
		logger.log(BG::Logger::ERROR, std::string("Failed to create window (") + SDL_GetError() + ")");
		SDL_DestroyWindow(window);
	}
	logger.log(BG::Logger::INFO, "Created window");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(renderer == nullptr)
	{
		// Render creation failed, report error, clean up and exit.
		logger.log(BG::Logger::ERROR, std::string("Failed to create renderer (") + SDL_GetError() + ")");
		SDL_DestroyRenderer(renderer);
	}
	logger.log(BG::Logger::INFO, "Created renderer");
}

/*
 * \brief Clears the Window's renderer ignoring the viewport and clip rectangle
 */
void BG::Window::clear() const
{
	SDL_RenderClear(renderer);
}

/*
 **	\brief Updates the Window's contents post rendering
 */
void BG::Window::display() const
{
	SDL_RenderPresent(renderer);
}

/*
 * \brief Destroys the Window and renderer freeing all associated memory
 */
void BG::Window::destroy()
{
	auto logger = Logger::getInstance();
	logger.log(Logger::INFO, "Destroying window");
	SDL_DestroyWindow(window);
	window = nullptr;
	logger.log(Logger::INFO, "Destroying renderer and freeing associated textures");
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
}

/*
 * \brief Render a GameObject to the Window
 * \param gameObject GameObject to render
 */
void BG::Window::draw(GameObject& gameObject) const
{
	Transform* transform = gameObject.getTransform();
	Vector2f position = transform->getPosition();
	float angle = transform->getRotation();

	Sprite* sprite = gameObject.getSprite();
	SDL_Texture* texture = sprite->getTexture();
	Vector2f size = sprite->getSize();
	SDL_RendererFlip flipped = sprite->getFlipped();
	Vector2f sprOrigin = sprite->getOrigin();

	SDL_Point origin = { sprOrigin.x, sprOrigin.y };
	SDL_Rect destination = { position.x, position.y, size.x, size.y };

	SDL_RenderCopyEx(renderer, texture, nullptr, &destination, angle, &origin, flipped);
}

/*
 * \brief Renders a GameObject to the Window tinted with the specified Colour
 * \param gameObject GameObject to render
 * \param tint tint Colour
 */
void BG::Window::draw(GameObject& gameObject, const Colour& tint) const
{
	SDL_SetTextureColorMod(gameObject.getSprite()->getTexture(), tint.r, tint.g, tint.b);
	draw(gameObject);
	SDL_SetTextureColorMod(gameObject.getSprite()->getTexture(), 255, 255, 255);
}

/*
 * \brief Renderers a FloatRect of the specified Colour to the Window 
 * \param rect FloatRect to render
 * \param colour rectangle colour
 */
void BG::Window::draw(const FloatRect& rect, const Colour& colour) const
{
	SDL_Rect bounds = { rect.left, rect.top, rect.width, rect.height };
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);
	SDL_RenderDrawRect(renderer, &bounds);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

/*
 * \brief Set the Window's position
 * \param position Window position
 */
void BG::Window::setPosition(const Vector2i& position) const
{
	SDL_SetWindowPosition(window, position.x, position.y);
}

/*
 * Returns the Window's current position
 */
BG::Vector2i BG::Window::getPosition() const
{
	Vector2i position = Vector2i(0, 0);
	SDL_GetWindowPosition(window, &position.x, &position.y);
	return position;
}

/*
 * \brief Set the Window's size
 * \param size Window size
 */
void BG::Window::setSize(const Vector2i& size) const
{
	SDL_SetWindowSize(window, size.x, size.y);
}

/*
 * \brief Returns the Window's current size
 */
BG::Vector2i BG::Window::getSize() const
{
	Vector2i size = Vector2i(0, 0);
	SDL_GetWindowSize(window, &size.x, &size.y);
	return size;
}

/*
 * \brief Set the fullscreen state of the Window
 * \brief state fullscreen state
 */
void BG::Window::setFullscreen(const bool& state) const
{
	SDL_SetWindowFullscreen(window, state ? SDL_WINDOW_FULLSCREEN : 0);
}

/*
 * \brief Set the Window's title
 * \param title Window title
 */
void BG::Window::setTitle(const std::string& title) const
{
	SDL_SetWindowTitle(window, title.c_str());
}

/*
 * \brief Returns a reference to the Window's renderer
 */
SDL_Renderer* BG::Window::getRenderer() const
{
	return renderer;
}

/*
 * \brief Returns true if the Window and its renderer initialized successfully
 */
bool BG::Window::isOpen() const
{
	return window != nullptr && renderer != nullptr;
}
