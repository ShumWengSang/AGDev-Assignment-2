#pragma once
#include "baseentity.h"
class Enemy :
	public BaseEntity
{
public:
	Enemy(void);
	~Enemy(void);
	 Matrix4x4 Scalef;


	bool glRenderObject(CVector3 theCameraPosition);
	bool glRenderObject(int RESOLUTION);

	 EntityType getObjectType(void);
	 CVector3 getPosition(void);
	 CVector3 getDirection();
	 CObjectModel GetObjectModel()
	 {
		 return  theObject;
	 }
	 CObjectModel theObject;


	 void SetPosition(CVector3 theNewPosition);
	 void SetScale(CVector3 theNewScale);

	 CVector3 GetScale();

	 CVector3 GetTopLeft()
	 {
		 MinMax ObjX = GetMinMax(theObject.theObj_LowPoly);

		 CVector3 TopLeft(ObjX.MinX, 0, ObjX.MaxZ );
		 TopLeft = TopLeft * Scalef;
		 TopLeft = TopLeft + CVector3(theObject.GetPosition().x, 0, theObject.GetPosition().z);

		// CVector3 result = TopLeft * Scalef;
		 return TopLeft;
	 }
	 CVector3 GetBottomRight()
	 {
		 MinMax ObjX = GetMinMax(theObject.theObj_LowPoly);

		 CVector3 BottomRight(ObjX.MaxX, 0, ObjX.MinZ);
		 BottomRight = BottomRight * Scalef;
		 BottomRight = BottomRight + CVector3(theObject.GetPosition().x, 0, theObject.GetPosition().z );

		 return BottomRight;
	 }
};

