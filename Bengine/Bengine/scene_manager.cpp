#include "scene_manager.h"
#include "scene.h"

/**
 * \brief Add a scene to the Scene Manager
 * \param scene_name scene's name
 * \param scene scene
 */
void BG::SceneManager::add_scene(const std::string& scene_name, Scene& scene)
{
	scenes_.insert(std::pair<std::string, Scene*>(scene_name, &scene));
}

/**
 * \brief Remove a scene from the Scene Manager
 * \param scene_name scene's name
 * \return removal successful
 */
bool BG::SceneManager::remove_scene(const std::string& scene_name)
{
	auto result = scenes_.find(scene_name);
	if(result != scenes_.end())
	{
		scenes_.erase(result);
		return true;
	}
	return false;
}

/**
 * \brief Transition to another scene
 * \param scene_name scene's name
 * \return transition successful
 */
bool BG::SceneManager::transition_to(const std::string& scene_name)
{
	if(current_scene_.second != nullptr)
	{
		auto result = scenes_.find(current_scene_.first);
		if(result != scenes_.end())
		{
			result->second->unload();
		}
	}

	current_scene_.second = nullptr;

	auto result = scenes_.find(scene_name);
	if(result != scenes_.end())
	{
		current_scene_ = std::pair<std::string, Scene*>(result->first, result->second);
		current_scene_.second->load();
	}

	return current_scene_.second != nullptr;
}

/**
 * \brief Returns a reference to the current scene
 */
BG::Scene& BG::SceneManager::current_scene() const
{
	return *current_scene_.second;
}

/**
 * \brief Returns the current scene's name
 */
std::string BG::SceneManager::current_scene_name() const
{
	return current_scene_.first;
}
