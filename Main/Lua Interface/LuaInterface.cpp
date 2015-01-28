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

float LuaInterface::GetFloat(char * name)
{
	lua_getglobal(L, name);
	float number = lua_tonumber(L, -1);
	return number;
}

bool LuaInterface::GetBool(char * name)
{
	lua_getglobal(L, name);
	bool number = lua_toboolean(L, -1);
	return number;
}


int LuaInterface::GetInt(char * name)
{
	lua_getglobal(L, name);
	int number = lua_tointeger(L, -1);
	return number;
}

char* LuaInterface::GetString(char * name)
{
	lua_getglobal(L, name);
	char * number = (char*)lua_tostring(L, -1);
	return number;
}