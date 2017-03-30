#pragma once
#include "scene.h"
#include "sprite.h"
#include "button.h"
#include "bengine_typedefs.h"
#include <vector>

namespace BG
{

	class ScnMainMenu : public Scene
	{

	public:

		explicit ScnMainMenu(Window& window);

		bool load() override;

		bool unload() override;

		bool update() override;

		bool draw() override;

	private:

		const Colour kColourBackground = Colour(102, 144, 184, 255);
		const float kCloudSpeed = 100.0f;
		const unsigned int kCloudRainPoolSize = 25;
		const std::vector<Colour> kCloudRainColours =
		{
			Colour(194, 84, 57, 255),
			Colour(211, 123, 51, 255),
			Colour(198, 187, 72, 255),
			Colour(119, 211, 124, 255)
		};

		Texture* txtr_title_;
		Texture* txtr_cloud_;
		Texture* txtr_box_;

		Texture* txtr_btn_play_idle_;
		Texture* txtr_btn_play_hovered_;
		Texture* txtr_btn_play_clicked_;

		Texture* txtr_btn_help_idle_;
		Texture* txtr_btn_help_hovered_;
		Texture* txtr_btn_help_clicked_;

		Texture* txtr_btn_exit_idle_;
		Texture* txtr_btn_exit_hovered_;
		Texture* txtr_btn_exit_clicked_;

		Music* mus_loop;
		
		SoundEffect* sfx_btn_click;
		SoundEffect* sfx_btn_hover;

		Button* btn_play_;
		Button* btn_help_;
		Button* btn_exit_;

		std::vector<Button*> buttons_;

		Sprite* spr_title_;
		Sprite* spr_cloud_;
		Sprite* spr_box_;

		GameObject* obj_title_;
		GameObject* obj_cloud_;

		std::vector<GameObject*> game_objects_;
		std::vector<GameObject*> cloud_rain_pool;

	};

}
