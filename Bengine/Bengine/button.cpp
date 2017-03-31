#include "button.h"
#include "resource_manager.h"
#include "Audio.h"
#include "game.h"

/**
 * \brief Creates a Button
 * \param position button position
 * \param texture_idle  idle texture
 * \param texture_hovered hovered texture
 * \param texture_clicked clicked texture
 * \param sfx_hover hover sound effect 
 * \param sfx_click click sound effect
 * \param window window
 */
BG::Button::Button(const Vector2f& position, Texture* texture_idle, Texture* texture_hovered, Texture* texture_clicked, SoundEffect* sfx_hover, SoundEffect* sfx_click, Window& window)
{
	ResourceManager* resource_manager = ResourceManager::instance();

	spr_idle_ = new Sprite(texture_idle, &window);
	spr_hovered_ = new Sprite(texture_hovered, &window);
	spr_clicked_ = new Sprite(texture_clicked, &window);

	sfx_hover_ = sfx_hover;
	sfx_click_ = sfx_click;

	game_object_ = GameObject(spr_idle_, position);

	mouse_ = Mouse::instance();

	clicked_ = false;
	hovered_ = false;
}

/**
 * \brief Returns a reference to the Button's underlying Game Object
 */
BG::GameObject& BG::Button::game_object()
{
	return game_object_;
}

/**
 * \brief Update the button, checking if it is hovered/clicked and changing its state accordingly
 */
void BG::Button::update()
{
	Vector2i mouse_pos_ = mouse_->position();
	Vector2f position_ = game_object_.transform().position();
	Vector2f size_ = game_object_.sprite().size();

	if (!(mouse_pos_.x_ >= position_.x_ && mouse_pos_.x_ <= position_.x_ + size_.x_ && mouse_pos_.y_ >= position_.y_ && mouse_pos_.y_ <= position_.y_ + size_.y_))
	{
		hovered_ = false;
		clicked_ = false;
		game_object_.set_sprite(spr_idle_);
		return;
	}

	if (mouse_->button_pressed(1))
	{
		if(!clicked_)
		{
			Audio::play_sound_effect(sfx_click_, 1, 0, 0);
			game_object_.set_sprite(spr_clicked_);
			clicked_ = true;
		}
	}
	else
	{
		clicked_ = false;
	}


	if(!hovered_)
	{
		Audio::play_sound_effect(sfx_hover_, 1, 0, 0);
		game_object_.set_sprite(spr_hovered_);
		hovered_ = true;
	}
}

/**
 * \brief Returns true if the button is currently clicked
 */
bool BG::Button::clicked() const
{
	return clicked_;
}