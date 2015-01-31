#pragma once
#include <vector>
#include <string>
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


// type that represents unused type parameters
typedef int(*lua_CFunction) (lua_State *L);

class LuaInterface
{
public:
	LuaInterface(void);
	~LuaInterface(void);



	bool RunScript(char * filename);
	bool LoadFile(char * filename);
	void Get(float &value, char * name);
	void Get(int& value, char * name);
	void Get(bool &value, char * name);
	void Get(char *value,char * name);
	void Get(std::string &value, char * name);
	void Pushfunction(char * FunctionName, lua_CFunction theFunction);

	void Push(const int &value)
	{
		lua_pushinteger(L, value);
	}

	void Push(const float &value)
	{
		lua_pushnumber(L, value);
	}

	void Push(const double &value)
	{
		lua_pushnumber(L, value);
	}
	void Push(const std::string &value)
	{
		lua_pushstring(L, value.c_str());
	}



private:
	lua_State * L;
};

