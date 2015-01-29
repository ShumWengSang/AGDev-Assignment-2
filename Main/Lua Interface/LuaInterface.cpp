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
	return true;
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

void LuaInterface::Get(float &value, char * name)
{
	lua_getglobal(L, name);
	value = lua_tonumber(L, -1);
}

void LuaInterface::Get(int& value, char * name)
{
	lua_getglobal(L, name);
	value = lua_toboolean(L, -1);

}


void LuaInterface::Get(bool &value, char * name)
{
	lua_getglobal(L, name);
	value = lua_tointeger(L, -1);

}

void LuaInterface::Get(char *value,char * name)
{
	lua_getglobal(L, name);
	value = (char*)lua_tostring(L, -1);

}