#pragma once
#include "BaseEntity.h"
#include "ObjectModel.h"
class CExit :
	public BaseEntity
{
public:
	CExit();
	~CExit();

	CVector3 getPosition(void);
	void SetPos(CVector3 newPos);

	bool glRenderObject(CVector3* theCameraPosition);

	EntityType getObjectType(void);
	CObjectModel theObject;
};

