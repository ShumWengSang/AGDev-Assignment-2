#include "LuaInterface.h"


LuaInterface::LuaInterface(void)
{
	L = lua_open();
	luaL_openlibs(L);
}


LuaInterface::~LuaInterface(void)
{
	lua_close(L);
}

bool LuaInterface::RunScript(char * filename)
{
	luaL_dofile(L,filename);
}

bool LuaInterface::LoadFile(char * filename)
{
	if(luaL_loadfile(L,filename) || lua_pcall(L,0,0,0))
	{
		printf("error: %s", lua_tostring(L,-1));
		return false;
	}
	return true;
}