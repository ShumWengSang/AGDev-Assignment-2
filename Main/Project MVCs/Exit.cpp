#include "Exit.h"


CExit::CExit()
{
}


CExit::~CExit()
{
}


CVector3 CExit::getPosition()
{
	return theObject.GetPosition();
}

void CExit::SetPos(CVector3 newPos)
{
	theObject.SetPosition(newPos);
}


bool CExit::glRenderObject(CVector3* theCameraPosition)
{
	theObject.Render(theCameraPosition);
	return true;
}

inline EntityType CExit::getObjectType(void)
{
	return EXIT;
}