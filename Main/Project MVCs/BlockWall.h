#pragma once
#include "Vector3.h"
#include "BaseEntity.h"

class BlockWall : public BaseEntity
{
public:
	BlockWall();
	~BlockWall();

	 bool glRenderObject(CVector3* theCameraPosition);
	 bool glRenderObject(int RESOLUTION);

	 EntityType getObjectType(void);


	 CVector3 getPosition(void);


	 CVector3 getDirection();


	 CObjectModel GetObjectModel()
	 {
		 CObjectModel theObject;
		 return  theObject;
	 }
	 CObjectModel theObjectX;
	 CObjectModel theObjectZ;

	 void SetPosition(CVector3 theNewPosition);
	 void SetScale(CVector3 theNewScale, bool LeftUp);
};

