#pragma once
#include "Vector3.h"
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "ObjLoader.h"
class CObjectModel
{
private:
	CVector3 thePosition;
	CVector3 theDirection;
	CVector3 Scale;



public:


	ObjFile theObj_HighPoly;
	ObjFile theObj_MedPoly;
	ObjFile theObj_LowPoly;

	CObjectModel(void);
	~CObjectModel(void);

	ObjFile * theCurrent;
	void Init(void);
	void Render(CVector3 theCameraPosition);
	void Render(const int RESOLUTION);
	void SetPosition(CVector3 theNewPosition);
	void SetDirection(CVector3 theNewDirection);
	void SetScale(CVector3 theNewScale);
	void SetOffset(CVector3 theNewOffset);
	CVector3 GetPosition();
	CVector3 GetDirection();
	CVector3 GetScale();
	int Texture;

	CVector3 TOffset;
};

