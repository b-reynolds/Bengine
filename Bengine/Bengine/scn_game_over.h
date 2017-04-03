#pragma once
#include "scene.h"
#include "Text.h"
#include "sprite.h"
#include "game_object.h"
#include "button.h"
#include <vector>

namespace BG
{

	class ScnGameOver : public BG::Scene
	{

	public:

		explicit ScnGameOver(Window& window, SceneManager& scene_manager);

		bool load() override;

		bool unload() override;

		bool update() override;

		bool draw() override;

	private:

		const std::string kBackgroundFilePath = "Images/Game Over/Background.png";

		const std::string kRetryButtonIdlePath = "Images/Game Over/ButtonRetryIdle.png";
		const std::string kRetryButtonHoveredPath = "Images/Game Over/ButtonRetryHovered.png";
		const std::string kRetryButtonClickedPath = "Images/Game Over/ButtonRetryClicked.png";
		
		const std::string kBackButtonIdlePath = "Images/Game Over/ButtonBackIdle.png";
		const std::string kBackButtonHoveredPath = "Images/Game Over/ButtonBackHovered.png";
		const std::string kBackButtonClickedPath = "Images/Game Over/ButtonBackClicked.png";

		const std::string kButtonClickPath = "Audio/ButtonClick.wav";
		const std::string kButtonHoverPath = "Audio/ButtonHover.wav";
		const std::string kMusicLoopPath = "Audio/EndLoop.mp3";
		const float kMusicLoopVolume = 128.0f;


		const std::string kFontFilePath = "Fonts/MetalReason.ttf";
		const int kScoreFontSize = 256;
		const int kHighScoreFontSize = 36;

		Font* fnt_score_;
		Font* fnt_high_score_;

		Text txt_score_;		
		Text txt_high_score_;

		Texture* txtr_background_;

		Texture* txtr_btn_retry_idle_;
		Texture* txtr_btn_retry_hovered_;
		Texture* txtr_btn_retry_clicked_;

		Texture* txtr_btn_back_idle_;
		Texture* txtr_btn_back_hovered_;
		Texture* txtr_btn_back_clicked_;

		SoundEffect* sfx_button_click_;
		SoundEffect* sfx_button_hover_;

		Music* mus_loop_;

		Button* btn_retry_;
		Button* btn_back_;

		std::vector<Button*> buttons_;

		Sprite* spr_background_;

		GameObject* obj_background_;

	};

}

