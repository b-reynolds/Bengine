#pragma once
#include "lua.hpp"
#include <string>

namespace BG
{
	class Lua
	{

	public:

		static Lua* instance();
		lua_State* state();

		void register_function(const std::string& name, lua_CFunction function);
		bool load_script(const std::string& script, std::string* error);

	private:

		static Lua* instance_;
		lua_State* state_;

		Lua();

	};
}