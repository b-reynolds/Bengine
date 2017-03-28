#include "button.h"
#include "resource_manager.h"
#include "Mouse.h"

BG::Button::Button(const Vector2f& position, Texture* texture_idle, Texture* texture_hovered, Texture* texture_clicked, Window& window)
{
	ResourceManager* resource_manager = ResourceManager::instance();

	spr_idle_ = new Sprite(texture_idle, &window);
	spr_hovered_ = new Sprite(texture_hovered, &window);
	spr_clicked_ = new Sprite(texture_clicked, &window);

	game_object_ = GameObject(spr_idle_, position);

	calculate_size();
}

BG::GameObject& BG::Button::game_object()
{
	return game_object_;
}

void BG::Button::update()
{

	Vector2i mouse_pos = Mouse::instance()->position();
	Sprite* spr_next;

	calculate_size();
	
	if (mouse_pos.x_ >= position_.x_ && mouse_pos.x_ <= position_.x_ + size_.x_ && mouse_pos.y_ >= position_.y_ && mouse_pos.y_ <= position_.y_ + size_.y_)
	{
		clicked_ = Mouse::instance()->button_down(1);
		spr_next = clicked_ ? spr_clicked_ : spr_hovered_;
	}
	else
	{
		clicked_ = false;
		spr_next = spr_idle_;
	}
	
	if(spr_next->texture() != game_object_.sprite().texture())
	{
		game_object_.set_sprite(spr_next);
	}

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
