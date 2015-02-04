#pragma once
#include "BaseEntity.h"
#include "ObjectModel.h"
class Player :
	public BaseEntity
{
public:
	Player();
	~Player();

	CVector3 getPosition(void);
	CVector3 getDirection();
	void SetDir(CVector3 newDir);
	void SetPos(CVector3 newPos);

	bool glRenderObject(CVector3 theCameraPosition);
	bool glRenderObject(int RESOLUTION);

	EntityType getObjectType(void);
	CObjectModel theObject;

	virtual CObjectModel GetObjectModel()
	{
		return theObject;
	}
private:


};

