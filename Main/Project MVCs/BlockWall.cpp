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
	theObjectZ.Render(RESOLUTION);
	theObjectX.Render(RESOLUTION);

	CVector3 TopLeft = GetTopLeft();
	CVector3 BottomRight = GetBottomRight();

	glBegin(GL_LINE);
	glVertex3f(TopLeft.x, 0 , TopLeft.z);
	glVertex3f(BottomRight.x, 0, TopLeft.z);
	glVertex3f(BottomRight.x, 0, BottomRight.z);
	glVertex3f(TopLeft.x, 0, BottomRight.z);
	glEnd();
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
			if (Increase)
			{
				theObjectX.SetScale(CVector3(theNewScale.x * 2, 1, 1));
			}
			else
			{
				theObjectX.SetScale(CVector3(theNewScale.x, 1, 1));
			}
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

			if (Increase)
			{
				theObjectX.SetScale(CVector3(theNewScale.x * 2, 1, 1));
			}
			else
			{
				theObjectX.SetScale(CVector3(theNewScale.x, 1, 1));
			}
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

			if (Increase)
			{
				theObjectZ.SetScale(CVector3(1, 1, theNewScale.z * 2));
			}
			else
			{
				theObjectZ.SetScale(CVector3(1, 1, theNewScale.z));
			}
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
			if (Increase)
			{
				theObjectZ.SetScale(CVector3(1, 1, theNewScale.z * 2));
			}
			else
			{
				theObjectZ.SetScale(CVector3(1, 1, theNewScale.z));
			}
		}
	}
}

CVector3 BlockWall::GetScale()
{
	return theScale;
}