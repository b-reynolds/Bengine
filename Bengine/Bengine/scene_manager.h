#pragma once
#include <map>

namespace BG
{
	class Scene;

	class SceneManager
	{

	public:

		void add_scene(const std::string& scene_name, Scene& scene);
		bool set_current_scene(const std::string& scene_name);

		Scene& current_scene() const;
		std::string current_scene_name() const;

	private:

		std::map<std::string, Scene*> scenes_;
		std::pair<std::string, Scene*> current_scene_;

	};

}