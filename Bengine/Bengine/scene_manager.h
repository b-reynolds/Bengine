#pragma once
#include <map>

namespace BG
{

	/* Forward declerations */
	class Scene;

	/*
	 * \brief Scene Manager class that handles transitioning between scenes
	 */
	class SceneManager
	{

	public:

		/* Add a scene to the Scene Manager */
		void add_scene(const std::string& scene_name, Scene& scene);

		bool remove_scene(const std::string& scene_name);

		/* Transition to another scene */
		bool transition_to(const std::string& scene_name);

		/* Returns a reference to the current scene */
		Scene& current_scene() const;

		/* Returns the current scene's name */
		std::string current_scene_name() const;

	private:

		/* Map of scenes */
		std::map<std::string, Scene*> scenes_;

		/* Currenty active scene */
		std::pair<std::string, Scene*> current_scene_;

	};

}