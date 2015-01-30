#include "Enemy.h"


Enemy::Enemy(void)
{
	theType = ENEMY;
}


Enemy::~Enemy(void)
{
}

bool Enemy::glRenderObject(CVector3* theCameraPosition)
{
	theObject.Render(theCameraPosition);

	return true;
}

bool Enemy::glRenderObject(int RESOLUTION)
{
	theObject.Render(RESOLUTION);

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

CVector3 Enemy::getPosition(void)
{
	return theObject.GetPosition();
}


CVector3 Enemy::getDirection()
{
	return theObject.GetDirection();
}

EntityType Enemy::getObjectType()
{
	return theType;
}

void Enemy::SetPosition(CVector3 theNewPosition)
{
	theObject.SetPosition(theNewPosition);
}

CVector3 Enemy::GetScale()
{
	return theObject.GetScale();
}

void Enemy::SetPosition(CVector3 theNewPosition)
{
	theObject.SetPosition(theNewPosition);
}
void Enemy::SetScale(CVector3 theNewScale)
{
	theObject.SetScale(theNewScale);
	Scalef.Scalef(theNewScale.x,theNewScale.y,theNewScale.z);
}