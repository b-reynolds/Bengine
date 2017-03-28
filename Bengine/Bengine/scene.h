#pragma once

namespace BG
{

	class Window;

	class Scene
	{

	public:

		Scene(Window& window) : window_(&window) {};

		virtual bool load() = 0;
		virtual bool unload() = 0;
		virtual bool update() = 0;
		virtual bool draw() = 0;

	protected:

		Window* window_;

	};

}