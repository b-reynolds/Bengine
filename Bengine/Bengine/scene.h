#pragma once
#include "scene_manager.h"

namespace BG
{
	/* Forward declerations */
	class Window;

	/*
	 * \brief Scene base class
	 */
	class Scene
	{

	public:

		/**
		 * \brief Construct a Scene
		 * \param window rendering window
		 * \param scene_manager scene manager
		 */
		Scene(Window& window, SceneManager& scene_manager) : window_(&window), scene_manager_(&scene_manager), loaded_(false) {}

		/* Virtual destructor*/
		virtual ~Scene() = default;

		/**
		 * \brief Load scene content
		 */
		virtual bool load() = 0;

		/**
		 * \brief Unload scene content
		 */
		virtual bool unload() = 0;


		/**
		 * \brief Update scene logic
		 */
		virtual bool update() = 0;

		/**
		 * \brief Render scene
		 */
		virtual bool draw() = 0;


		/**
		 * \brief Returns User controlled loaded flag
		 */
		bool loaded() const;

	protected:

		/**
		 * \brief Window the scene will be rendered to
		 */
		Window* window_;


		/**
		 * \brief Scene manager used for scene transitions
		 */
		SceneManager* scene_manager_;

		/**
		 * \brief User controlled flag, scenes will not be rendered until they are loaded
		 */
		bool loaded_;

	};

	/**
	 * \brief Returns User controlled loaded flag
	 */
	inline bool Scene::loaded() const
	{
		return loaded_;
	}
}
