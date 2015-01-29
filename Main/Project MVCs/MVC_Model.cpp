//*************************************************************************************************************************************//
//
//	Original MVC framework made by Mr Toh Da Jun for DM2231 Game Development Techniques
//	Adapted and modified by Kennard Kee Wei Sheng
//	Framework taken with permission by Shum Weng Sang
//************************************************************************************************************************************//

#include "MVC_Model.h"

static void TestFunction()
{
	std::cout << "ITS WORKING" << std::endl;
}


MVC_Model::MVC_Model(void):
theCamera(ThirdPerson),
Camera2(FirstPerson),
theQuadTree(0, rect(theBox.GetRight(), theBox.GetNear(), theBox.Width, theBox.Length))
{

	Rotate = 0;
	m_timer=MVCTime::GetInstance();
	distance = 10;
	ObjectAngle = 0;
	PlayerID = 0;
	//thePlayerData.theFrustum = &theFrustum;
	theExits = NULL;
	DebugCam = true;
}

MVC_Model::~MVC_Model(void)
{

	delete[] theExits;
	theExits = NULL;
}

bool MVC_Model::Init(float fpsLimit)
{
	m_timer->Init(true,int(fpsLimit));
	m_moveX=m_moveY=0;

	return true;
}

bool MVC_Model::InitPhase2(void)
{
	m_testX=m_worldSizeX*0.5f;
	m_testY=m_worldSizeY*0.5f;

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )


	if (!LoadTGA(&SkyBoxTextures[0], "SkyBox/front.tga"))				// Load The Font Texture
		return false;	// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[1], "SkyBox/back.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[2], "SkyBox/left.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[3], "SkyBox/right.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[4], "SkyBox/top.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[5], "SkyBox/bottom.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False

	//Find the ratio between skybox width and height and maze width and height.
	//We need this to fully fill our skybox with the maze.
	float ratiox = theBox.Width / MAZEWIDTH;
	float ratioy = theBox.Length / MAZEHEIGHT;

	MazeGenerator theMaze;
	BlockWall * newWall;
	ObjFile thecube = LoadOBJ("Objects/Cube.obj");
	theMaze.Draw();
	for (int MazeWidth = -0; MazeWidth < MAZEWIDTH; MazeWidth++)
	{
		for (int MazeHeight = -0; MazeHeight < MAZEHEIGHT; MazeHeight++)
		{
			if (theMaze.theMaze[MazeWidth][MazeHeight] == 0)
			{
				continue;
			}
			else
			{
				newWall = new BlockWall;
				newWall->theObjectX.theObj_LowPoly = thecube;
				newWall->theObjectZ.theObj_LowPoly = thecube;

				newWall->SetPosition(CVector3((float)(MazeWidth - MAZEWIDTH / 2) * ratiox, 0, (float)(MazeHeight - MAZEHEIGHT / 2)* ratioy));


				if (theMaze.theMaze[MazeWidth + 1][MazeHeight] == 1 &&MazeWidth+1<MAZEWIDTH)
				{
					newWall->SetScale(CVector3(ratiox, newWall->GetScale().y, newWall->GetScale().z), false);
				}
				if (theMaze.theMaze[MazeWidth - 1][MazeHeight] == 1 &&MazeWidth>0)
				{
					newWall->SetScale(CVector3(ratiox, newWall->GetScale().y, newWall->GetScale().z), true);
				}
				if (theMaze.theMaze[MazeWidth][MazeHeight + 1]==1 && MazeHeight+1<MAZEHEIGHT)
				{
					newWall->SetScale(CVector3(newWall->GetScale().x, newWall->GetScale().y, ratioy), true);
				}
				if (theMaze.theMaze[MazeWidth][MazeHeight - 1] == 1 && MazeHeight>0)
				{
					newWall->SetScale(CVector3(newWall->GetScale().x, newWall->GetScale().y, ratioy), false);
				}
				theListofObjects.push_back(newWall);
			}
		}
	}

	newWall = new BlockWall;
	newWall->theObjectX.theObj_LowPoly = thecube;
	newWall->theObjectZ.theObj_LowPoly = thecube;
	newWall->SetPosition(CVector3((float)(theMaze.x - MAZEWIDTH / 2) * ratiox, 0, (float)(theMaze.z - MAZEHEIGHT / 2)* ratioy));
	theListofObjects.push_back(newWall);

	newWall = new BlockWall;
	newWall->theObjectX.theObj_LowPoly = thecube;
	newWall->theObjectZ.theObj_LowPoly = thecube;
	newWall->SetPosition(CVector3(0,10,0));
	theListofObjects.push_back(newWall);

	//if (!LoadTGA(&ExitTexture[0], "exit.tga"))				// Load The Font Texture
		//return false;	// If Loading Failed, Return False


	
	//if (!LoadTGA(&theImageDebugger, "steel.tga"))				// Load The Font Texture
		//return false;										// If Loading Failed, Return False

	glDisable(GL_TEXTURE_2D);								



	for (int i = 0; i < 6; i++)
	{
		theBox.textureID[i] = SkyBoxTextures[i].texID;//Set the TEX ID into the SkyBox itself
	}


	for (int i = 0; i < theListofObjects.size(); i++)
	{
		theQuadTree.insert(theListofObjects[i]);
	}

	//Generate the Maze and input it.



	return true;
}

// Update the model
void MVC_Model::Update(void)
{
	if(DebugCam)
	{
		Camera2.SetDT(m_timer->GetDelta());
		Camera2.Update();
	}
	else
	{
		theCamera.SetDT(m_timer->GetDelta());
		theCamera.Update();
	}
	if (m_timer->TestFramerate())
	{
		m_testX += m_moveX*m_timer->GetDelta();
		m_testY += m_moveY*m_timer->GetDelta();
	}

	if (m_timer->TestFramerate())
	{
		//PlayerAgainstExit(PlayerID, theExits, theMaze.PossibleExits.size());
		//CheckCollision();
	}
}

//Checking specific to the root.
//void MVC_Model::FrustumChecking()
//{
//	for (int i = 0; i < theRoot.GetNumOfChild(); i++)
//	{
//		const int ID = theRoot.GetSceneNodeID() * 10 + i + 1;
//		FrustumChecking(theRoot.GetNode(ID), theRoot.GetSceneNodeID(), ID);
//	}
//}
//
//void MVC_Model::FrustumChecking(CSceneNode * thisNode, const int ParentID, const int thisID)
//{
//	Vector3D NearTopLeft, NearTopRight, NearBottomLeft, NearBottomRight;
//	Vector3D FarTopLeft, FarTopRight, FarBottomLeft, FarBottomRight;
//
//	NearTopLeft = thisNode ->GetNearTopLeft();
//	NearTopRight = thisNode->GetNearTopRight();
//	NearBottomLeft = thisNode->GetNearBottomLeft();
//	NearBottomRight = thisNode->GetNearBottomRight();
//
//	FarTopLeft = thisNode->GetFarTopLeft();
//	FarTopRight = thisNode->GetFarTopRight();
//	FarBottomLeft = thisNode->GetFarBottomLeft();
//	FarBottomRight = thisNode->GetFarBottomRight();
//	{
//
//		bool m_bCheckNearTopLeft = theFrustum.ContainmentCheck(NearTopLeft);
//		bool m_bCheckNearTopRight = theFrustum.ContainmentCheck(NearTopRight);
//		bool m_bCheckNearBottomLeft = theFrustum.ContainmentCheck(NearBottomLeft);
//		bool m_bCheckNearBottomRight = theFrustum.ContainmentCheck(NearBottomRight);
//
//		bool m_bCheckFarTopLeft = theFrustum.ContainmentCheck(FarTopLeft);
//		bool m_bCheckFarTopRight = theFrustum.ContainmentCheck(FarTopRight);
//		bool m_bCheckFarBottomLeft = theFrustum.ContainmentCheck(FarBottomLeft);
//		bool m_bCheckFarBottomRight = theFrustum.ContainmentCheck(FarBottomRight);
//
//
//		if (!(m_bCheckNearTopLeft || m_bCheckNearTopRight
//			|| m_bCheckNearBottomLeft || m_bCheckNearBottomRight
//			|| m_bCheckFarTopLeft || m_bCheckFarTopRight
//			|| m_bCheckFarBottomLeft || m_bCheckFarBottomRight))
//		{
//			//The scene graph is not inside the frustum
//			//thisNode->SetColor(0, 0, 0);
//			thisNode->Draw();
//		}
//
//		else
//		{
//			if (m_bCheckNearTopLeft && m_bCheckNearTopRight
//				&& m_bCheckNearBottomLeft && m_bCheckNearBottomRight
//				&& m_bCheckFarTopLeft && m_bCheckFarTopRight
//				&& m_bCheckFarBottomLeft && m_bCheckFarBottomRight)
//			{
//				// The scene graph is inside the frustum!
//				//thisNode->SetColor(1.0f, 1.0f, 1.0f);
//				//thisNode->Draw();
//			}
//
//			else
//			{
//				//thisNode->Draw();
//				//thisNode->SetColor(1, 0, 0);
//				//Scene graph halfway in.
//			}
//			for (int i = 0; i < thisNode->GetNumOfChild(); i++)
//			{
//				const int ID = thisNode->GetSceneNodeID() * 10 + i + 1;
//				FrustumChecking(thisNode->GetNode(ID), thisID, ID);
//			}
//		}
//	}
//}


//Check Collision. Since only the player is moving, we only need to check the player
//against the world. All other collision  settings will only add to processing memory.
//void MVC_Model::CheckCollision()
//{
//	for (int i = 0; i < theRoot.GetNumOfChild(); i++)
//	{
//		const int ID = theRoot.GetSceneNodeID() * 10 + i + 1;
//		if (ID != PlayerID)
//			CheckCollision(theRoot.GetNode(PlayerID), theRoot.GetNode(ID));
//	}
//}
//
//void MVC_Model::CheckCollision(CSceneNode * otherNode, CSceneNode * thisNode)
//{
//	//We only need to check 4 sides, since we don't move along the Y axis.
//	//(x,z) to (-x,z)
//	//(x,z) to (x,-z)
//	//(-x,z) to (-x,-z)
//	//(x,-z) to (-x,-z)
//	Vector3D NearTopRight;
//	Vector3D FarBottomLeft;
//	Vector3D FarTopRight;
//	Vector3D NearBottomLeft;
//
//	Vector3D OtherVectors[4];
//
//	NearTopRight = thisNode->GetNearTopRight();
//	FarBottomLeft = thisNode->GetFarBottomLeft();
//	NearBottomLeft = thisNode->GetNearBottomLeft();
//	FarTopRight = thisNode->GetFarTopRight();
//
//	//Check Collision with the root.
//	OtherVectors[0] = otherNode->GetNearTopRight();
//	OtherVectors[1] = otherNode->GetFarBottomLeft();
//	OtherVectors[2] = otherNode->GetNearBottomLeft();
//	OtherVectors[3] = otherNode->GetFarTopRight();
//
//	for (int i = 0; i < 4; i++)
//	{
//		if (IsPointInside(OtherVectors[i], FarTopRight, NearBottomLeft)
//			|| IsPointInside(OtherVectors[i], NearBottomLeft, FarTopRight))
//		{
//			cout << "COLLIDED" << i << endl;
//		}
//	}
//
//	for (int i = 0; i < theRoot.GetNode(PlayerID)->GetNumOfChild(); i++)
//	{
//		const int childID = PlayerID * 10 + i + 1;
//		otherNode->GetNearTopRight(childID,OtherVectors[0]);
//		otherNode->GetFarBottomLeft(childID, OtherVectors[1]);
//		otherNode->GetNearBottomLeft(childID, OtherVectors[2]);
//		otherNode->GetFarTopRight(childID, OtherVectors[3]);
//
//		for (int j = 0; j < 4; j++)
//		{
//			if (IsPointInside(OtherVectors[j], FarTopRight, NearBottomLeft)
//				|| IsPointInside(OtherVectors[j], NearBottomLeft, FarTopRight))
//			{
//				cout << "COLLIDED " << "Child: "<< childID << " Collide: "<< j << endl;
//				theRoot.GetNode(childID)->SetColor(1, 1, 1);
//			}
//		}
//	}
//
//	//TEST
//	//OtherVectors[0] = otherNode->GetNearTopRight();
//	//OtherVectors[1] = otherNode->GetFarBottomLeft();
//	//OtherVectors[2] = otherNode->GetNearBottomLeft();
//	//OtherVectors[3] = otherNode->GetFarTopRight();
//
//	//for (int i = 0; i < 4; i++)
//	//{
//	//	if (IsPointInside(OtherVectors[i], FarTopRight, NearBottomLeft)
//	//		|| IsPointInside(OtherVectors[i], NearBottomLeft, FarTopRight))
//	//	{
//	//		cout << "COLLIDED" << i << endl;
//	//	}
//	//}
//
//	//OtherVectors[0] = otherNode->GetNearTopLeft();
//	//OtherVectors[1] = otherNode->GetNearTopRight();
//	//OtherVectors[2] = otherNode->GetNearBottomLeft();
//	//OtherVectors[3] = otherNode->GetNearBottomRight();
//
//	//OtherVectors[4] = otherNode->GetFarTopLeft();
//	//OtherVectors[5] = otherNode->GetFarTopRight();
//	//OtherVectors[6] = otherNode->GetFarBottomLeft();
//	//OtherVectors[7] = otherNode->GetFarBottomRight();
//	//
//
//	
//}

//bool MVC_Model::IsPointInside(Vector3D thePoint, Vector3D Min, Vector3D Max)
//{
//	if (thePoint.m_x > Min.m_x && thePoint.m_x < Max.m_x &&
//		thePoint.m_z > Min.m_z && thePoint.m_z < Max.m_z)
//	{
//		return true;
//	}
//	return false;
//}
//
//void MVC_Model::PlayerAgainstExit(int PlayerID, Entity Exit[], int size)
//{
//	for (int i = 0; i < size; i++)
//	{
//
//		Vector3D NearTopRight (-1,1,-1);
//		Vector3D FarBottomLeft(1, -1, 1);
//		Vector3D FarTopRight(1, 1, -1);
//		Vector3D NearBottomLeft(-1, -1, 1);
//
//		NearTopRight += Exit[i].GetPos();
//		FarBottomLeft += Exit[i].GetPos();
//		FarTopRight += Exit[i].GetPos();
//		NearBottomLeft += Exit[i].GetPos();
//
//		CSceneNode * thePlayer = theRoot.GetNode(PlayerID);
//
//		Vector3D OtherVectors[4];
//		//Check Collision with the root.
//		OtherVectors[0] = thePlayer->GetNearTopRight();
//		OtherVectors[1] = thePlayer->GetFarBottomLeft();
//		OtherVectors[2] = thePlayer->GetNearBottomLeft();
//		OtherVectors[3] = thePlayer->GetFarTopRight();
//
//		for (int j = 0; j < 4; j++)
//		{
//			if (IsPointInside(OtherVectors[j], FarTopRight, NearBottomLeft)
//				|| IsPointInside(OtherVectors[j], NearBottomLeft, FarTopRight))
//			{
//				cout << "COLLIDED WITH EXIT" << endl;
//			}
//		}
//	}
//}

