#pragma once



#include <windows.h> // Header File For Windows
#include <gl\gl.h> // Header File For The OpenGL32 Library
#include <gl\glu.h> // Header File For The GLu32 Library
#include "Vector3.h"
#include "camera.h"
#include "TGALoader.cpp"

class HUD
{
public:
	HUD(void);
	~HUD(void);

	void GetCameraDirection(CVector3 CamDir);
	CVector3 theCamDir;

	CCamera * theCamera;
	TextureImage theMinimap;
	void DrawMinimap();
	void Draw();
	void DrawHealthBar(const int m_iHealth, const int m_iMaxHealth);

	int m_iHeightOfBar;
	int m_iWidthOfBar;

	void SetHUD(bool);
	
};
