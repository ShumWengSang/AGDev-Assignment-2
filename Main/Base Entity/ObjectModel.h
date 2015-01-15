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
	ObjFile theObj_HighPoly;
	ObjFile theObj_MedPoly;
	ObjFile theObj_LowPoly;

public:
	CObjectModel(void);
	~CObjectModel(void);

	void Init(void);
	void Render(CVector3* theCameraPosition);
	void Render(const int RESOLUTION);
	void SetPosition(CVector3 theNewPosition);
	CVector3 GetPosition();
};

