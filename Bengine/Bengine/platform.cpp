#include "platform.h"
#include "resource_manager.h"
#include "World.h"
#include "Box2D/Dynamics/b2Fixture.h"

const int Platform::kTileSize = 128;

int Platform::platform_count_ = 0;

Platform::Platform(const BG::Vector2f& position, const unsigned int& length, BG::Window* window)
{
	spr_center_ = new BG::Sprite(BG::ResourceManager::instance()->texture(kPlatformCenter, window), window);
	spr_center_->set_size(BG::Vector2f(kTileSize, kTileSize));

	spr_left_edge_ = new BG::Sprite(BG::ResourceManager::instance()->texture(kPlatformLeftEdge, window), window);
	spr_left_edge_->set_size(BG::Vector2f(kTileSize, kTileSize));

	spr_right_edge_ = new BG::Sprite(BG::ResourceManager::instance()->texture(kPlatformRightEdge, window), window);
	spr_right_edge_->set_size(BG::Vector2f(kTileSize, kTileSize));

	BG::Vector2f segment_position = position;

	for(unsigned int i = 0; i < length; ++i)
	{
		BG::GameObject* segment;

		if(i == 0)
		{
			segment = new BG::GameObject(spr_left_edge_, BG::Vector2f(0.0f, 0.0f));
		}
		else if(i == length - 1)
		{
			segment = new BG::GameObject(spr_right_edge_, BG::Vector2f(0.0f, 0.0f));
		}
		else
		{
			segment = new BG::GameObject(spr_center_, BG::Vector2f(0.0f, 0.0f));
		}
		
		segment->init_physics(b2_kinematicBody, 0.0f, BG::Vector2f(0.0f, 0.0f));
		segment->set_position(segment_position);
		segments_.push_back(segment);

		segment_position.x_ += kTileSize;
	}

	platform_count_++;
}

Platform::~Platform()
{
	if(platform_count_ == 1)
	{
		BG::ResourceManager::instance()->free_texture(kPlatformLeftEdge);
		BG::ResourceManager::instance()->free_texture(kPlatformCenter);
		BG::ResourceManager::instance()->free_texture(kPlatformRightEdge);

	}

	for(unsigned int i = 0; i < segments_.size(); ++i)
	{
		BG::World::instance()->DestroyBody(segments_[i]->rigidbody());
		delete segments_[i];
	}

	platform_count_--;
}

void Platform::set_position(const BG::Vector2f& position)
{
	for(unsigned int i = 0; i < segments_.size(); ++i)
	{
		if (i == 0)
		{
			segments_[i]->set_position(position);
			continue;
		}

		segments_[i]->set_position(BG::Vector2f(segments_[i - 1]->position().x_ + kTileSize, segments()[i - 1]->position().y_));
	}
}

BG::FloatRect Platform::bounds()
{
	return BG::FloatRect(segments_[0]->position().x_, segments_[0]->position().y_, kTileSize * segments_.size(), kTileSize);
}

const std::vector<BG::GameObject*>& Platform::segments() const
{
	return segments_;
}
