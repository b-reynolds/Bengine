#pragma once
#include "scene.h"
#include "player.h"
#include "platform.h"
#include <vector>
#include "Text.h"
#include "timer.h"
#include "keyboard.h"

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

		/* ---- Score ---- */

		const std::string kScoreFontFilePath = "Fonts/MetalReason.ttf";
		const int kScoreTextSize = 150;
		const int kScoreIncrement = 10;

		int score_;

		Font* fnt_score_;
		Text txt_score_;

		Timer tmr_score_;

		void update_score();

		/* ------------------------------ */

		/* ---- Music ---- */

		const std::string kMusicLoopFilePath = "Audio/GameLoop.mp3";
		const float kMusicLoopVolume = 128.0f;

		Music* mus_loop_;

		/* ------------------------------ */

		/* ---- Scrolling Background ---- */

		const std::string kBackgroundSegOneFilePath = "Images/Game/Background1.png";
		const std::string kBackgroundSegTwoFilePath = "Images/Game/Background2.png";
		const float kBackgroundScrollSpeedDefault = 100.0f;
		const float kBackgroundScrollSpeedIncrement = 1.0f;

		float background_scroll_speed_;

		Texture* txtr_background_;
		Texture* txtr_background_2_;

		Sprite* spr_background_;
		Sprite* spr_background_2_;

		GameObject* obj_background_;
		GameObject* obj_background_2_;

		void update_background() const;

		/* ------------------------------ */

		/* ---- Platforms ---- */

		const float kPlatformSpeedDefault = 1000.0f;
		const float kPlatformSpeedIncrement = 1.0f;

		const int kPlatformTilesMin = 2;
		const int kPlatformTilesMax = 5;
		const int kPlatformRowsMax = 3;
		const int kPlatformSpaceProbability = 5;
		const int kPlatformSpaceTilesMin = 0;
		const int kPlatformSpaceTilesMax = 2;

		float platform_speed_;
		float end_platform_x_;

		std::vector<Platform*> platforms_;

		void update_platforms();

		/* ------------------------------ */

		/* ---- Player ---- */

		Player* player_;

		float player_desired_x_;

		void update_player();

		/* ------------------------------ */

		/* ---- Input ---- */

		Keyboard* keyboard_;

		/* ------------------------------ */

	};

}
