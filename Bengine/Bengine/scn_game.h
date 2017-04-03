#pragma once
#include "scene.h"
#include "player.h"
#include "platform.h"
#include <vector>
#include "Text.h"
#include "timer.h"

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

		const Colour kBackgroundColour = Colour(102, 144, 184, 255);

		const int kPlatformTilesMin = 0;

		const unsigned int kPlatformPoolSize = 50;

		const int kSpaceChance = 5;
		const int kSpaceMin = 1;
		const int kSpaceMax = 2;

		const int kPlatformRows = 3;


		const int kPlatformTilesMax = 6;

		const int kScorePerSecond = 100;

		int score_;

		float end_platform_x_;

		void update_platforms();

		float platform_speed_;

		Texture* txtr_player_;
		Texture* txtr_background_;
		Texture* txtr_background_2_;

		Music* mus_loop_;

		Sprite* spr_player_;
		Sprite* spr_background_;
		Sprite* spr_background_2_;

		GameObject* obj_background_;
		GameObject* obj_background_2_;

		Text txt_score_;

		Font* fnt_score_;

		Timer tmr_score_;


		Player player_;

		std::vector<Platform*> platforms_;

	};

}
