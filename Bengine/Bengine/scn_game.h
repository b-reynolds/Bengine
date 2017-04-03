#pragma once
#include "scene.h"
#include "player.h"
#include "platform.h"
#include <vector>

namespace BG
{

	class ScnGame : public Scene
	{

	public:

		explicit ScnGame(Window& window, SceneManager& scene_manager);

		bool load() override;

		bool unload() override;

		bool update() override;

		bool draw() override;

	private:

		const int kPlatformTilesMin = 0;

		const unsigned int kPlatformPoolSize = 50;

		const int kPlatformTilesMax = 6;

		float end_platform_x_;

		void update_platforms();

		float platform_speed_;

		Texture* txtr_player_;

		Sprite* spr_player_;

		Player player_;

		std::vector<Platform*> platforms_;

	};

}
