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

		explicit ScnMainMenu(Window& window, SceneManager& scene_manager);

		bool load() override;

		bool unload() override;

		bool update() override;

		bool draw() override;

	private:

		const Colour kBackgroundColour = Colour(0, 0, 0, 255);

		Texture* txtr_background_;

		Texture* txtr_btn_play_idle_;
		Texture* txtr_btn_play_hovered_;
		Texture* txtr_btn_play_clicked_;

		Texture* txtr_btn_exit_idle_;
		Texture* txtr_btn_exit_hovered_;
		Texture* txtr_btn_exit_clicked_;

		Music* mus_loop_;
		
		SoundEffect* sfx_btn_click_;
		SoundEffect* sfx_btn_hover;

		Button* btn_play_;
		Button* btn_exit_;

		std::vector<Button*> buttons_;

		Sprite* spr_background_;

		GameObject* obj_background_;

		std::vector<GameObject*> game_objects_;

	};

}
