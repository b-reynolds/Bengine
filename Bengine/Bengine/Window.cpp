#include "window.h"
#include "Logger.h"
#include "game_object.h"
#include "colour.h"
#include "Text.h"

/*
 * \brief Creates and initializes a Window with the specified title and of the specified size
 * \param title Window title
 * \param size Window size
 */
BG::Window::Window(const std::string& title, const Vector2u& size)
{
	window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.x_, size.y_, SDL_WINDOW_OPENGL);

	auto logger = Logger::instance();

	if(window_ == nullptr)
	{
		// Window creation failed, report error, clean up and exit.
		logger.log(BG::Logger::kError, std::string("Failed to create window (") + SDL_GetError() + ")");
		SDL_DestroyWindow(window_);
	}
	logger.log(BG::Logger::kInfo, "Created window");

	clr_background_ = BG::kClrBlack;

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(renderer_ == nullptr)
	{
		// Render creation failed, report error, clean up and exit.
		logger.log(BG::Logger::kError, std::string("Failed to create renderer (") + SDL_GetError() + ")");
		SDL_DestroyRenderer(renderer_);
	}
	logger.log(BG::Logger::kInfo, "Created renderer");
}

/*
 * \brief Clears the Window's renderer ignoring the viewport and clip rectangle
 */
void BG::Window::clear() const
{
	SDL_RenderClear(renderer_);
}

/*
 **	\brief Updates the Window's contents post rendering
 */
void BG::Window::display() const
{
	SDL_RenderPresent(renderer_);
}

/*
 * \brief Destroys the Window and renderer freeing all associated memory
 */
void BG::Window::destroy()
{
	auto logger = Logger::instance();
	logger.log(Logger::kInfo, "Destroying window");
	SDL_DestroyWindow(window_);
	window_ = nullptr;
	logger.log(Logger::kInfo, "Destroying renderer and freeing associated textures");
	SDL_DestroyRenderer(renderer_);
	renderer_ = nullptr;
}

/*
 * \brief Render text to the window
 * \param Text text to be rendered
 */
void BG::Window::draw(Text& text) const
{
	Texture* texture = text.texture();
	Transform transform = text.transform();
	Vector2f txtPosition = transform.position();
	Vector2f txtOrigin = text.origin();
	float txtAngle = transform.rotation();

	SDL_Rect dstRect = { txtPosition.x_, txtPosition.y_, 0, 0 };
	SDL_Point origin = { text.origin().x_, text.origin().y_ };

	SDL_QueryTexture(texture, nullptr, nullptr, &dstRect.w, &dstRect.h);
	SDL_RenderCopyEx(renderer_, texture, nullptr, &dstRect, txtAngle, &origin, SDL_FLIP_NONE);
	SDL_DestroyTexture(texture);
}

/*
 * \brief Render a GameObject to the Window
 * \param gameObject GameObject to render
 */
void BG::Window::draw(GameObject& gameObject) const
{
	Transform* transform = gameObject.transform();
	Vector2f position = transform->position();
	float angle = transform->rotation();

	Sprite* sprite = gameObject.sprite();
	SDL_Texture* texture = sprite->texture();
	Vector2f size = sprite->size();
	SDL_RendererFlip flipped = sprite->flipped();
	Vector2f sprOrigin = transform->origin();

	SDL_Point origin = { sprOrigin.x_, sprOrigin.y_ };
	SDL_Rect destination = { position.x_, position.y_, size.x_, size.y_ };

	SDL_RenderCopyEx(renderer_, texture, nullptr, &destination, angle, &origin, flipped);
}

/*
 * \brief Renders a GameObject to the Window tinted with the specified Colour
 * \param gameObject GameObject to render
 * \param tint tint Colour
 */
void BG::Window::draw(GameObject& gameObject, const Colour& tint) const
{
	SDL_SetTextureColorMod(gameObject.sprite()->texture(), tint.r_, tint.g_, tint.b_);
	draw(gameObject);
	SDL_SetTextureColorMod(gameObject.sprite()->texture(), 255, 255, 255);
}

/*
 * \brief Renderers a FloatRect of the specified Colour to the Window 
 * \param rect FloatRect to render
 * \param colour rectangle colour
 */
void BG::Window::draw(const FloatRect& rect, const Colour& colour) const
{
	SDL_Rect bounds = { rect.left_, rect.top_, rect.width_, rect.height_ };
	SDL_SetRenderDrawColor(renderer_, colour.r_, colour.g_, colour.b_, colour.a_);
	SDL_RenderDrawRect(renderer_, &bounds);
	SDL_SetRenderDrawColor(renderer_, clr_background_.r_, clr_background_.g_, clr_background_.b_, clr_background_.a_);
}

/*
 * \brief Set the Window's position
 * \param position Window position
 */
void BG::Window::set_position(const Vector2i& position) const
{
	SDL_SetWindowPosition(window_, position.x_, position.y_);
}

/*
 * Returns the Window's current position
 */
BG::Vector2i BG::Window::position() const
{
	Vector2i position = Vector2i(0, 0);
	SDL_GetWindowPosition(window_, &position.x_, &position.y_);
	return position;
}

/*
 * \brief Set the Window's size
 * \param size Window size
 */
void BG::Window::set_size(const Vector2i& size) const
{
	SDL_SetWindowSize(window_, size.x_, size.y_);
}

/*
 * \brief Returns the Window's current size
 */
BG::Vector2i BG::Window::size() const
{
	Vector2i size = Vector2i(0, 0);
	SDL_GetWindowSize(window_, &size.x_, &size.y_);
	return size;
}

/*
 * \brief Set the fullscreen state of the Window
 * \brief state fullscreen state
 */
void BG::Window::set_fullscreen(const bool& state) const
{
	SDL_SetWindowFullscreen(window_, state ? SDL_WINDOW_FULLSCREEN : 0);
}

/*
 * \brief Set the Window's title
 * \param title Window title
 */
void BG::Window::set_title(const std::string& title) const
{
	SDL_SetWindowTitle(window_, title.c_str());
}

/*
 * \brief Returns a reference to the Window's renderer
 */
SDL_Renderer* BG::Window::renderer() const
{
	return renderer_;
}

/*
 * \brief Returns true if the Window and its renderer initialized successfully
 */
bool BG::Window::open() const
{
	return window_ != nullptr && renderer_ != nullptr;
}
