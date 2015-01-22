#pragma once
#include "ComGTGALoad.h"
#include <vector>
#include "camera.h"
#include "SkyBox.h"
#include "Player.h"
#include "Mouse.h"
#include "Math2.h"
#include "Frustum.h"
#include "HUD.h"
#include "Exit.h"
#include "MVCtime.h"


class MVCTime;

class MVC_Model
{
public:
	MVC_Model(void);
	~MVC_Model(void);
	// Update the model
	void Update(void);
	bool Init(float fpsLimit);
	bool InitPhase2(void);//init after view's init e.g Textures,stuff requiring screen size
	float Rotate;
	
	float m_worldSizeX;
	float m_worldSizeY;

	float m_testX;
	float m_testY;
	float m_moveX,m_moveY;

	CVector3 FrustumPosition;
	CVector3 FrustumDirection;

	TextureImage SkyBoxTextures[6];
	TextureImage ExitTexture[6];

	CExit * theExits;

	MVCTime* m_timer;
	CFrustum theFrustum;

	int PlayerID;

	Player thePlayerData;

	CCamera theCamera;
	CCamera Camera2;

	HUD theHUD;
	SkyBox theBox;

	//void FrustumChecking();
	//void FrustumChecking(CSceneNode* thisNode, const int ParentID, const int thisID);

	//void CheckCollision();
	//void CheckCollision(CSceneNode * otherNode, CSceneNode * thisNode);
	//bool IsPointInside(CVector3, CVector3, CVector3);

	//A function just for checking the exits against the player in the scene graph
	//void PlayerAgainstExit(int PlayerID, Entity Exit[], int size);

	//A vector to hold the IDs of the parts to rotate.
	//std::vector<int> ArrayofIDs;

	//DISTANCE FROM OBJECT TO CAMERA
	int distance;

	//TESTING CODES
	float x, y, z;

	//MAZE
	//MazeGenerator theMaze;
	TextureImage theImageDebugger;

	//Rotate the object
	float ObjectAngle;

	//Choose camera debug purposes
	int ChooseCamera;

	int PlayerParts[4];
private: 
};
