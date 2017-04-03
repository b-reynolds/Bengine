#pragma once
#include "scene.h"
#include "sprite.h"
#include "button.h"
#include <vector>

namespace BG
{

	class ScnHelpScreen : public Scene
	{

	public:

		explicit ScnHelpScreen(Window& window, SceneManager& scene_manager);

		bool load() override;

		bool unload() override;

		bool update() override;

		bool draw() override;

	private:

		const Colour kBackgroundColour = Colour(102, 144, 184, 255);

		Texture* txtr_title_;

		Texture* txtr_btn_back_idle_;
		Texture* txtr_btn_back_hovered_;
		Texture* txtr_btn_back_clicked_;

		Sprite* spr_title_;

		SoundEffect* sfx_btn_hover_;
		SoundEffect* sfx_btn_click_;

		Music* mus_loop;

		Button* btn_back_;

		GameObject* obj_title_;

		std::vector<GameObject*> game_objects_;
		std::vector<Button*> buttons_;

	};

}
