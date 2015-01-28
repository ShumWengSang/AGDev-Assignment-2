#include "BlockWall.h"


BlockWall::BlockWall()
{
	theType = HorizontalWall;
	theScale.Set(1, 1, 1);
}


BlockWall::~BlockWall()
{
}

bool BlockWall::glRenderObject(CVector3* theCameraPosition)
{
	theObjectZ.Render(theCameraPosition);
	theObjectX.Render(theCameraPosition);
	return true;
}

bool BlockWall::glRenderObject(int RESOLUTION)
{
	//theObjectZ.Render(RESOLUTION);
	//theObjectX.Render(RESOLUTION);

	CVector3 TopLeft = GetTopLeft();
	CVector3 BottomRight = GetBottomRight();
	this;
	glColor3f(1, 1, 1);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(TopLeft.x, 10 , TopLeft.z);
	glVertex3f(BottomRight.x, 10, TopLeft.z);
	glVertex3f(BottomRight.x, 10, BottomRight.z);
	glVertex3f(TopLeft.x, 10, BottomRight.z);
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
	bool Increase = false;
	if (theNewScale.x != 1)
	{
		if (LeftUp)
		{
			CVector3 theOrigPos = theObjectX.GetPosition();
			if (theObjectX.GetScale().x != 1)
			{
				Increase = true;
			}
			theOrigPos.Set(theOrigPos.x - (theNewScale.x / 2), theOrigPos.y, theOrigPos.z);
			theObjectX.SetPosition(theOrigPos);
		}
		else
		{
			CVector3 theOrigPos = theObjectX.GetPosition();
			if (theObjectX.GetScale().x != 1)
			{
				Increase = true;
			}
			theOrigPos.Set(theOrigPos.x + (theNewScale.x / 2), theOrigPos.y, theOrigPos.z);
			theObjectX.SetPosition(theOrigPos);
		}
		if (Increase)
		{
			theObjectX.SetScale(CVector3(theNewScale.x * 2, 1, 1));
			theScale.Set(theNewScale.x * 2, 1, theObjectZ.GetScale().z);
			Scalef.Scalef(theNewScale.x * 2, 1, theObjectZ.GetScale().z);
		}
		else
		{
			theObjectX.SetScale(CVector3(theNewScale.x, 1, 1));
			theScale.Set(theNewScale.x, 1, theObjectZ.GetScale().z);
			Scalef.Scalef(theNewScale.x, 1, theObjectZ.GetScale().z);
		}
	}

	if (theNewScale.z != 1)
	{
		if (LeftUp)
		{
			CVector3 theOrigPos = theObjectZ.GetPosition();
			if (theObjectX.GetScale().x != 1)
			{
				Increase = true;
			}
			theOrigPos.Set(theOrigPos.x , theOrigPos.y, theOrigPos.z + (theNewScale.z / 2));
			theObjectZ.SetPosition(theOrigPos);

		}
		else
		{
			CVector3 theOrigPos = theObjectZ.GetPosition();
			if (theObjectZ.GetScale().z != 1)
			{
				Increase = true;
			}
			theOrigPos.Set(theOrigPos.x, theOrigPos.y, theOrigPos.z - (theNewScale.z / 2));
			theObjectZ.SetPosition(theOrigPos);
		}
		if (Increase)
		{
			theObjectZ.SetScale(CVector3(1, 1, theNewScale.z * 2));
			theScale.Set(theObjectX.GetScale().x, 1, theNewScale.z * 2);
			Scalef.Scalef(theObjectX.GetScale().x, 1, theNewScale.z * 2);
		}
		else
		{
			theObjectZ.SetScale(CVector3(1, 1, theNewScale.z));
			theScale.Set(theObjectX.GetScale().x, 1, theNewScale.z);
			Scalef.Scalef(theObjectX.GetScale().x, 1, theNewScale.z);

		}
	}
}

CVector3 BlockWall::GetScale()
{
	return theScale;
}