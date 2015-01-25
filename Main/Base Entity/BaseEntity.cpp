#include "BaseEntity.h"


BaseEntity::BaseEntity()
{
	theType = NONE;
}


BaseEntity::~BaseEntity()
{
}

bool BaseEntity::glRenderObject(CVector3* theCameraPosition)
{
	return false;
};


EntityType BaseEntity::getObjectType(void)
{
	return theType;
};


CVector3 BaseEntity::getPosition(void)
 { 
	 CVector3 t; return t;
 };

CVector3 BaseEntity::getDirection()
{
	CVector3 t; return t;
}


bool BaseEntity::operator == (BaseEntity& o)
{
	return bool(getObjectType() == o.getObjectType() && getPosition() == o.getPosition());
}

CObjectModel BaseEntity::GetObjectModel()
{
	CObjectModel t;
	return t;
}

bool BaseEntity::glRenderObject(int RESOLUTION)
{
	return false;
}