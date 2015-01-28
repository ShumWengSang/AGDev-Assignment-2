#pragma once
#include <vector>
#include <string>
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


class LuaInterface
{
public:
	LuaInterface(void);
	~LuaInterface(void);

	lua_State * L;

	bool RunScript(char * filename);
	bool LoadFile(char * filename);
	float GetFloat(char * name);
	int GetInt(char * name);
	bool GetBool(char * name);
	char* GetString(char * name);
};

