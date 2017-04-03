#pragma once
#include "game_object.h"
#include <vector>

class Platform
{

public:

	static const int kTileSize;

	explicit Platform(const BG::Vector2f& position, const unsigned int& length, BG::Window* window);
	~Platform();

	void set_position(const BG::Vector2f& position);

	BG::FloatRect bounds();

	const std::vector<BG::GameObject*>& segments() const;

private:

	const std::string kPlatformLeftEdge = "Images/Game/PlatformLeftEdge.png";
	const std::string kPlatformRightEdge = "Images/Game/PlatformRightEdge.png";
	const std::string kPlatformCenter = "Images/Game/PlatformCenter.png";

	static int platform_count_;

	std::vector<BG::GameObject*> segments_;

	BG::Sprite* spr_left_edge_;
	BG::Sprite* spr_right_edge_;
	BG::Sprite* spr_center_;

};

