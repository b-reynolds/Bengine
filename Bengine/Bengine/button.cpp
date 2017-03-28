#include "button.h"
#include "resource_manager.h"
#include "Audio.h"
#include "game.h"

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
}

BG::GameObject& BG::Button::game_object()
{
	return game_object_;
}

void BG::Button::update()
{
	mouse_pos_ = mouse_->position();
	position_ = game_object_.transform().position();
	size_ = game_object_.sprite().size();

	if (!(mouse_pos_.x_ >= position_.x_ && mouse_pos_.x_ <= position_.x_ + size_.x_ && mouse_pos_.y_ >= position_.y_ && mouse_pos_.y_ <= position_.y_ + size_.y_))
	{
		hovered_ = false;
		clicked_ = false;
		game_object_.set_sprite(spr_idle_);
		return;
	}

	if (mouse_->button_down(1))
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

	//Sprite* spr_next;

	//calculate_size();
	//
	//if (mouse_pos_.x_ >= position_.x_ && mouse_pos_.x_ <= position_.x_ + size_.x_ && mouse_pos_.y_ >= position_.y_ && mouse_pos_.y_ <= position_.y_ + size_.y_)
	//{
	//	clicked_ = Mouse::instance()->button_down(1);

	//	if(!hovered_)
	//	{
	//		Audio::play_sound_effect(clicked_ ? sfx_click_ : sfx_hover_, 1, 0, 0);
	//	}

	//	hovered_ = true;

	//	spr_next = clicked_ ? spr_clicked_ : spr_hovered_;
	//}
	//else
	//{
	//	hovered_ = false;
	//	clicked_ = false;
	//	spr_next = spr_idle_;
	//}
	//
	//if(spr_next->texture() != game_object_.sprite().texture())
	//{
	//	game_object_.set_sprite(spr_next);
	//}

}

bool BG::Button::clicked() const
{
	return clicked_;
}

void BG::Button::calculate_size()
{
	position_ = game_object_.transform().position();
	size_ = game_object_.sprite().size();
}
;