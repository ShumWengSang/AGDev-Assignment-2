#include "BlockWall.h"


BlockWall::BlockWall()
{
	theType = HorizontalWall;
	theScale.Set(1, 1, 1);
}


BlockWall::~BlockWall()
{
}

bool BlockWall::glRenderObject(CVector3 theCameraPosition)
{
	theObjectZ.Render(theCameraPosition);
	theObjectX.Render(theCameraPosition);
	return true;
}

bool BlockWall::glRenderObject(int RESOLUTION)
{
	theObjectZ.Render(RESOLUTION);
	theObjectX.Render(RESOLUTION);

	CVector3 TopLeft = GetTopLeft();
	CVector3 BottomRight = GetBottomRight();
	this;
	glColor3f(1, 1, 1);
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glVertex3f(TopLeft.x, 10 , TopLeft.z);
	glVertex3f(BottomRight.x, 10, TopLeft.z);
	glVertex3f(BottomRight.x, 10, BottomRight.z);
	glVertex3f(TopLeft.x, 10, BottomRight.z);
	glVertex3f(TopLeft.x, 10, TopLeft.z);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(TopLeft.x, 10, TopLeft.z);
	glVertex3f(TopLeft.x, 0, TopLeft.z);
	glVertex3f(TopLeft.x, 0, BottomRight.z);
	glVertex3f(TopLeft.x, 10, BottomRight.z);
	glVertex3f(TopLeft.x, 10, TopLeft.z);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(BottomRight.x, 10, TopLeft.z);
	glVertex3f(BottomRight.x, 0, TopLeft.z);
	glVertex3f(BottomRight.x, 0, BottomRight.z);
	glVertex3f(BottomRight.x, 10, BottomRight.z);
	glVertex3f(BottomRight.x, 10, TopLeft.z);
	glEnd();

	glPopMatrix();
	return true;
}

CVector3 BlockWall::getPosition(void)
{
	return theObjectX.GetPosition();
}


CVector3 BlockWall::getDirection()
{
	return theObjectX.GetDirection();
}

EntityType BlockWall::getObjectType()
{
	return theType;
}

void BlockWall::SetPosition(CVector3 theNewPosition)
{
	theObjectX.SetPosition(theNewPosition);
	theObjectZ.SetPosition(theNewPosition);
}

void BlockWall::SetScale(CVector3 theNewScale, bool LeftUp)
{
	theObjectX.SetScale(CVector3(theNewScale.x, 1, 1));
	theObjectZ.SetScale(CVector3(1, 1, theNewScale.z));
	theScale.Set(theNewScale.x, 1, theNewScale.z);
	Scalef.Clear();
	Scalef.Scalef(theNewScale.x, 1, theNewScale.z);
	//bool Increase = false;
	//if (theNewScale.x != 1)
	//{
	//	if (LeftUp)
	//	{
	//		CVector3 theOrigPos = theObjectX.GetPosition();
	//		if (theObjectX.GetScale().x != 1)
	//		{
	//			Increase = true;
	//		}
	//		theOrigPos.Set(- (theNewScale.x / 2), 0, 0);
	//		theObjectX.SetOffset(theOrigPos);
	//	}
	//	else
	//	{
	//		CVector3 theOrigPos = theObjectX.GetPosition();
	//		if (theObjectX.GetScale().x != 1)
	//		{
	//			Increase = true;
	//		}
	//		theOrigPos.Set((theNewScale.x / 2), 0, 0);
	//		theObjectX.SetOffset(theOrigPos);
	//	}
	//	if (Increase)
	//	{
	//		theObjectX.SetScale(CVector3(theNewScale.x + theObjectX.GetScale().x, 1, 1));
	//		theScale.Set(theNewScale.x +theScale.x, 1, theObjectZ.GetScale().z);
	//		Scalef.Scalef(theNewScale.x, 1, theScale.z);
	//	}
	//	else
	//	{
	//		theObjectX.SetScale(CVector3(theNewScale.x, 1, 1));
	//		theScale.Set(theNewScale.x, 1, theObjectZ.GetScale().z);
	//		Scalef.Scalef(theNewScale.x, 1, theScale.z);
	//	}
	//}

	//if (theNewScale.z != 1)
	//{
	//	if (LeftUp)
	//	{
	//		CVector3 theOrigPos = theObjectZ.GetPosition();
	//		if (theObjectZ.GetScale().z != 1)
	//		{
	//			Increase = true;
	//		}
	//		theOrigPos.Set(0 , 0,  (theNewScale.z / 2));
	//		theObjectZ.SetOffset(theOrigPos);

	//	}
	//	else
	//	{
	//		CVector3 theOrigPos = theObjectZ.GetPosition();
	//		if (theObjectZ.GetScale().z != 1)
	//		{
	//			Increase = true;
	//		}
	//		theOrigPos.Set(0, 0,  - (theNewScale.z / 2));
	//		theObjectZ.SetOffset(theOrigPos);
	//	}
	//	if (Increase)
	//	{
	//		theObjectZ.SetScale(CVector3(1, 1, theNewScale.z + theObjectZ.GetScale().z));
	//		theScale.Set(theObjectX.GetScale().x, 1, theNewScale.z + theScale.z);
	//		Scalef.Scalef(theScale.x, 1, theNewScale.z);
	//	}
	//	else
	//	{
	//		theObjectZ.SetScale(CVector3(1, 1, theNewScale.z));
	//		theScale.Set(theObjectX.GetScale().x, 1, theNewScale.z);
	//		Scalef.Scalef(theScale.x, 1, theNewScale.z);

	//	}
	//}
}

CVector3 BlockWall::GetScale()
{
	return theScale;
}