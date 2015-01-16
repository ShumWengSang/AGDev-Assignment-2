#pragma once
#include <vector>
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}


class LuaInterface
{
public:
	LuaInterface(void);
	~LuaInterface(void);

	lua_State * L;

	bool RunScript(char * filename);
	bool LoadFile(char * filename);
};

