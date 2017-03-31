#pragma once
#include "scene.h"
#include "sprite.h"

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

		const Colour kColourBackground = Colour(255, 0, 0, 255);

	};

}