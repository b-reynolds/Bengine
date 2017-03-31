#include "scene_manager.h"
#include "scene.h"

void BG::SceneManager::add_scene(const std::string& scene_name, Scene& scene)
{
	scenes_.insert(std::pair<std::string, Scene*>(scene_name, &scene));
}

bool BG::SceneManager::set_current_scene(const std::string& scene_name)
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

BG::Scene& BG::SceneManager::current_scene() const
{
	return *current_scene_.second;
}

std::string BG::SceneManager::current_scene_name() const
{
	return current_scene_.first;
}
