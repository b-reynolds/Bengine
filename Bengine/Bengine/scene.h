#pragma once
#include "scene_manager.h"

namespace BG
{

	class Window;

	class Scene
	{

	public:
		virtual ~Scene() = default;

		Scene(Window& window, SceneManager& scene_manager) : window_(&window), scene_manager_(&scene_manager), loaded_(false) {}

		virtual bool load() = 0;
		virtual bool unload() = 0;
		virtual bool update() = 0;
		virtual bool draw() = 0;

		bool loaded() const;

	protected:

		Window* window_;
		SceneManager* scene_manager_;

		bool loaded_;

	};

	inline bool Scene::loaded() const
	{
		return loaded_;
	}
}
