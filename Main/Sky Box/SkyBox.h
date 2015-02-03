#pragma once
#include <windows.h> // Header File For Windows
#include <gl\gl.h> // Header File For The OpenGL32 Library
#include <gl\glu.h> // Header File For The GLu32 Library
#include "LuaInterface.h"
class SkyBox
{
public:
	SkyBox();
	~SkyBox();

	int textureID[6];
	void Draw();

	float Height, Width, Length;
	float GetTop();
	float GetBottom();
	float GetLeft();
	float GetRight();
	float GetNear();
	float GetFar();
	float GetLength();
private:

	void Init();

	float Top;
	float Bottom;
	float Left;
	float Right;
	float Near;
	float Far;
};
