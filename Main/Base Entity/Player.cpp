#include "Player.h"


Player::Player()
{
	theType = PLAYER;
}


Player::~Player()
{

}


CVector3 Player::getPosition()
{
	return theObject.GetPosition();
}

void Player::SetPos(CVector3 newPos)
{
	theObject.SetPosition(newPos);
}

CVector3 Player::getDirection()
{
	return theObject.GetDirection();
}

void Player::SetDir(CVector3 newPos)
{
	theObject.SetDirection(newPos);
}


bool Player::glRenderObject(CVector3* theCameraPosition)
{
	theObject.Render(theCameraPosition);
	return true;
}

inline EntityType Player::getObjectType(void)
{
	return PLAYER;
}