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

		const float kPlatformTileSize = 64.0f;

		void update_platforms();

		float platform_speed_;

		Texture* txtr_player_;

		Sprite* spr_player_;

		Player player_;

		std::vector<Platform*> platforms_;

	};

}
