#pragma once
#include "game_object.h"
#include <string>
#include <vector>

class Platform
{

public:

	static const int kTileSize;

	explicit Platform(const BG::Vector2f& position, const unsigned int& length, BG::Window* window);
	~Platform();

	void set_position(const BG::Vector2f& position);

	BG::FloatRect bounds();

	b2Body& rigidbody() const;

	const std::vector<BG::GameObject*>& segments() const;

private:

	const std::string kPlatformLeftEdge = "Images/Platforms/PlatformLeftEdge.png";
	const std::string kPlatformRightEdge = "Images/Platforms/PlatformRightEdge.png";
	const std::string kPlatformCenter = "Images/Platforms/PlatformCenter.png";
	const std::string kPlatformTexture = "Images/Platforms/Platform.png";

	static int platform_count_;

	const std::vector<BG::Colour> kSegmentColours =
	{
		BG::Colour(194, 84, 57, 255),
		BG::Colour(211, 123, 51, 255),
		BG::Colour(198, 187, 72, 255),
		BG::Colour(119, 211, 124, 255)
	};

	std::vector<BG::GameObject*> segments_;

	BG::Sprite* spr_block_;
	BG::Sprite* spr_left_edge_;
	BG::Sprite* spr_right_edge_;
	BG::Sprite* spr_center_;

};

