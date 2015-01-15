#include "ObjectModel.h"


CObjectModel::CObjectModel(void)
: thePosition(0, 0, 0)
, theObj_HighPoly(0)
, theObj_MedPoly(0)
, theObj_LowPoly(0)
{
}

CObjectModel::~CObjectModel(void)
{
}

void CObjectModel::Init(void)
{
	theObj_HighPoly = LoadOBJ("./ObjectModels/Cylinder_High.obj");
	theObj_MedPoly = LoadOBJ("./ObjectModels/Cylinder_Med.obj");
	theObj_LowPoly = LoadOBJ("./ObjectModels/Cylinder_Low.obj");
}

void CObjectModel::Render(CVector3* theCameraPosition)
{
	CVector3 theDistance(theCameraPosition->x - thePosition.x,
		theCameraPosition->y - thePosition.y,
		theCameraPosition->z - thePosition.z);
	float distance = theDistance.GetMagnitude();

	glPushMatrix();

	glTranslatef(thePosition.x, thePosition.y, thePosition.z);
	if (distance < 30)
	{
		DrawOBJ(theObj_HighPoly);
	}
	else if (distance < 60)
	{
		DrawOBJ(theObj_MedPoly);
	}
	else
	{
		DrawOBJ(theObj_LowPoly);
	}

	glPopMatrix();
}

void CObjectModel::Render(const int RESOLUTION)
{
	glPushMatrix();
	glTranslatef(thePosition.x, thePosition.y, thePosition.z);
	if (RESOLUTION == 0)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		DrawOBJ(theObj_HighPoly);
	}
	else if (RESOLUTION == 1)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		DrawOBJ(theObj_MedPoly);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		DrawOBJ(theObj_LowPoly);
	}
	glPopMatrix();
}

void CObjectModel::SetPosition(CVector3 theNewPosition)
{
	thePosition.Set(theNewPosition.x, theNewPosition.y, theNewPosition.z);
}

CVector3 CObjectModel::GetPosition()
{
	return CVector3(thePosition.x, thePosition.y, thePosition.z);
}
