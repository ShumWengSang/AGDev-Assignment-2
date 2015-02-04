#include "ObjectModel.h"


CObjectModel::CObjectModel(void)
: thePosition(0, 0, 0)
, theObj_HighPoly(0)
, theObj_MedPoly(0)
, theObj_LowPoly(0)
{
	Scale.Set(1,1,1);
	TOffset.Set(0, 0, 0);
}

CObjectModel::~CObjectModel(void)
{
}

void CObjectModel::Init(void)
{

}

void CObjectModel::Render(CVector3 theCameraPosition)
{
	CVector3 theDistance(theCameraPosition.x - thePosition.x,
		theCameraPosition.y - thePosition.y,
		theCameraPosition.z - thePosition.z);
	float distance = theDistance.GetMagnitude();
	glPushMatrix();

	glTranslatef(thePosition.x, thePosition.y, thePosition.z);
	//glTranslatef(TOffset.x, TOffset.y, TOffset.z);
	glScalef(Scale.x, Scale.y, Scale.z);
	if (distance < 30)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		//DrawOBJ(theObj_HighPoly);
		DrawOBJ(theObj_LowPoly);
	}
	else if (distance < 60)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		//DrawOBJ(theObj_MedPoly);
		DrawOBJ(theObj_LowPoly);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		//DrawOBJ(theObj_MedPoly);
		DrawOBJ(theObj_LowPoly);
	}

	glPopMatrix();
}

void CObjectModel::Render(const int RESOLUTION)
{
	glPushMatrix();
	glTranslatef(thePosition.x, thePosition.y, thePosition.z);
	//glTranslatef(TOffset.x, TOffset.y, TOffset.z);
	glScalef(Scale.x, Scale.y, Scale.z);
	if (RESOLUTION == 0)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		//DrawOBJ(theObj_HighPoly);
		DrawOBJ(theObj_LowPoly);
	}
	else if (RESOLUTION == 1)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		//DrawOBJ(theObj_MedPoly);
		DrawOBJ(theObj_LowPoly);
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


void CObjectModel::SetDirection(CVector3 theNewDirection)
{
	theDirection.Set(theNewDirection.x, theNewDirection.y, theNewDirection.z);
}

CVector3 CObjectModel::GetDirection()
{
	return CVector3(theDirection.x, theDirection.y, theDirection.z);
}

void CObjectModel::SetScale(CVector3 theNewScale)
{
	Scale.Set( theNewScale);
}

CVector3 CObjectModel::GetScale()
{
	return Scale;
}

void CObjectModel::SetOffset(CVector3 theNewOffset)
{
	TOffset.Set(theNewOffset);
}