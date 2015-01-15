#include "BaseEntity.h"


BaseEntity::BaseEntity()
{
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
	return NONE;
};


const CVector3 BaseEntity::getPosition(void)
 { 
	 CVector3 t; return t;
 };




bool BaseEntity::operator == (BaseEntity& o)
{
	return bool(getObjectType() == o.getObjectType() && getPosition() == o.getPosition());
}
