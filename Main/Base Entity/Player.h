#pragma once
#include "BaseEntity.h"
#include "ObjectModel.h"
class Player :
	public BaseEntity
{
public:
	Player();
	~Player();

	const CVector3 getPosition(void);
	void SetPos(CVector3 newPos);

	bool glRenderObject(CVector3* theCameraPosition);

	inline EntityType getObjectType(void);
	CObjectModel theObject;
private:


};

