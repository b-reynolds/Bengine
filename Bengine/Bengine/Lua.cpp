//#include "Lua.h"
//
//BG::Lua* BG::Lua::instance_ = nullptr;
//
//BG::Lua* BG::Lua::instance()
//{
//	if(instance_ == nullptr)
//	{
//		instance_ = new Lua();
//	}
//	return instance_;
//}
//
//lua_State* BG::Lua::state()
//{
//	return state_;
//}
//
//void BG::Lua::register_function(const std::string& name, lua_CFunction function)
//{
//	lua_register(state_, name.c_str(), function);
//}
//
//bool BG::Lua::load_script(const std::string& script, std::string* error)
//{
//	int result = luaL_loadstring(state_, script.c_str());
//	if(result)
//	{
//		if(error != nullptr)
//		{
//			*error = lua_tostring(state_, -1);
//		}
//		return false;
//	}
//	return true;
//}
//
//BG::Lua::Lua()
//{
//	state_ = luaL_newstate();
//	luaL_openlibs(state_);
//}
